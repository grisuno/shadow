# Gotchas

## God Nodes (high connectivity)

These files have the most connections. Changes here have high blast radius.

- `shadow.c` (score: 1.20)
- `server.py` (score: 0.70)

## Hotspots (complexity + centrality)

- `shadow.c` -- complexity: 1.0, centrality: 1.0, combined: 1.0
- `server.py` -- complexity: 0.6, centrality: 0.5, combined: 0.5

## Dataflow Issues (INFERRED, review each lead)

- `server.py:148` `dns_server` [UNCHECKED_ALLOC] `sock`: Result of allocator stored in `sock` is never checked against NULL.
