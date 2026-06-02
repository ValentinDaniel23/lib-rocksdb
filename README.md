# lib-rocksdb

Unikraft port of RocksDB.

This is a pure library port, similar in integration style to `lib-leveldb`.
Application entrypoints belong in apps (for example
`catalog-core/rocksdb/main.cpp`), not in this library.

## Upstream Source

The library fetches upstream RocksDB automatically during build from:

- `https://github.com/facebook/rocksdb/archive/refs/tags/v11.1.1.tar.gz`

No local `LIBROCKSDB_UPSTREAM` checkout path is required.

## Port Notes

- `snapshot_checker_compat.cc` is intentionally kept. Using upstream
  `utilities/transactions/snapshot_checker.cc` pulls additional transaction-db
  symbols that are not part of this port's selected source set.
- `src/env/unique_id_gen.cc` is a local override used by this port to keep
  unique-id generation robust when random device access can throw.
- Build uses release-style assertions disabled (`NDEBUG`) for runtime
  stability on constrained targets.
- Port uses default C++ thread integration (`CXX_THREADS`) and does not force
  `LIBPTHREAD_EMBEDDED`.
