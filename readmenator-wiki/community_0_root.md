# root

*Community 0 | 2 files | cohesion 1.00*

## Definition

This community groups 2 file(s) rooted at `root` with dominant language py (cohesion 1.00). Central symbols: `BEACON_INTERVAL`, `C2_DOMAIN`, `DNS_PORT`, `DNS_SERVER`, `_GNU_SOURCE`, `build_dns_query`, `build_dns_response`, `c2_thread`. Core file: `shadow.c` (12 symbols). Documented purpose: Servidor DNS C2 – robusto y funcional sudo python3 server_dns.py.

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `server.py` | py | utility | 7 | yes |
| `shadow.c` | c | utility | 12 | no |

## Key Symbols

- `encode_b64` (function, `server.py:17`) `def encode_b64(data)`
- `decode_b64` (function, `server.py:20`) `def decode_b64(data)`
- `decode_dns_name` (function, `server.py:27`) `def decode_dns_name(data, pos)` - Decodifica un nombre DNS (puede tener compresión)
- `build_dns_response` (function, `server.py:49`) `def build_dns_response(query_data, answer_name, qtype, qclass, rdata_str, ttl)` - Construye respuesta DNS con registro A o TXT
- `handle_query` (function, `server.py:77`) `def handle_query(data, addr, sock)`
- `dns_server` (function, `server.py:147`) `def dns_server()`
- `cmd_input` (function, `server.py:156`) `def cmd_input()`
- `_GNU_SOURCE` (macro, `shadow.c:6`) `#define _GNU_SOURCE`
- `DNS_SERVER` (macro, `shadow.c:21`) `#define DNS_SERVER`
- `DNS_PORT` (macro, `shadow.c:22`) `#define DNS_PORT`
- `C2_DOMAIN` (macro, `shadow.c:23`) `#define C2_DOMAIN`
- `BEACON_INTERVAL` (macro, `shadow.c:24`) `#define BEACON_INTERVAL`
- `encode_b64` (function, `shadow.c:29`) `static void encode_b64(const unsigned char *in, size_t len, char *out)`
- `decode_b64` (function, `shadow.c:42`) `static void decode_b64(const char *in, unsigned char *out, size_t *out_len)`
- `build_dns_query` (function, `shadow.c:68`) `static int build_dns_query(uint16_t id, const char *name, int qtype, unsigned ch` - else if (c == '-') val = 62; else if (c == '_') val = 63; else continue; n = (n << 6) \| val; bits +=
- `dns_query` (function, `shadow.c:98`) `static int dns_query(const char *name, int qtype, unsigned char *response, size_` - buf[pos++] = len; memcpy(buf + pos, p, len); pos += len; p = dot ? dot + 1 : p + strlen(p); } buf[po
- `run_cmd` (function, `shadow.c:128`) `static char *run_cmd(const char *cmd)` - } struct timeval tv = {5, 0}; setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)); struct soc
- `c2_thread` (function, `shadow.c:161`) `static void *c2_thread(void *arg)` - buf[n] = '\0'; output = realloc(output, total + n + 1); if (!output) { close(pipefd[0]); return strd
- `main` (function, `shadow.c:224`) `int main(int argc, char **argv)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 0
- Cross-boundary resolved imports (EXTRACTED): 0

## Connections

- No cross-community bridges recorded. This community is self-contained.

## Risks

- [dataflow UNCHECKED_ALLOC] `server.py:148` `dns_server` `sock`: Result of allocator stored in `sock` is never checked against NULL.

## Open Questions

- Why do 1 file(s) lack file-level docs (e.g. `shadow.c`)? What purpose do they serve?
- What would break if the most connected file in root changed?
- Should root be split, given cohesion 1.00?

## Sources

- `server.py`
- `shadow.c`
