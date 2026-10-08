# Subsystem: root

## server.py
- Layer: utility
- Doc: Servidor DNS C2 – robusto y funcional sudo python3 server_dns.py
- Language: py
- Symbols:
  - `encode_b64` (function, line 17) `def encode_b64(data)`
  - `decode_b64` (function, line 20) `def decode_b64(data)`
  - `decode_dns_name` (function, line 27) `def decode_dns_name(data, pos)`
  - `build_dns_response` (function, line 49) `def build_dns_response(query_data, answer_name, qtype, qclass, rdata_str, ttl)`
  - `handle_query` (function, line 77) `def handle_query(data, addr, sock)`
  - `dns_server` (function, line 147) `def dns_server()`
  - `cmd_input` (function, line 156) `def cmd_input()`

## shadow.c
- Layer: utility
- Language: c
- Symbols:
  - `encode_b64` (function, line 29) `static void encode_b64(const unsigned char *in, size_t len, char *out)`
  - `decode_b64` (function, line 42) `static void decode_b64(const char *in, unsigned char *out, size_t *out_len)`
  - `build_dns_query` (function, line 68) `static int build_dns_query(uint16_t id, const char *name, int qtype, unsigned char *buf)`
  - `dns_query` (function, line 98) `static int dns_query(const char *name, int qtype, unsigned char *response, size_t *resp_len)`
  - `run_cmd` (function, line 128) `static char *run_cmd(const char *cmd)`
  - `c2_thread` (function, line 161) `static void *c2_thread(void *arg)`
  - `main` (function, line 224) `int main(int argc, char **argv)`
  - `_GNU_SOURCE` (macro, line 6) `#define _GNU_SOURCE`
  - `DNS_SERVER` (macro, line 21) `#define DNS_SERVER`
  - `DNS_PORT` (macro, line 22) `#define DNS_PORT`
  - `C2_DOMAIN` (macro, line 23) `#define C2_DOMAIN`
  - `BEACON_INTERVAL` (macro, line 24) `#define BEACON_INTERVAL`
