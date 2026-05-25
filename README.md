# lib-rocksdb

Unikraft port of RocksDB.

This is a pure library port, similar in integration style to `lib-leveldb`.
Application entrypoints should live in the app (for example
`catalog-core/rocksdb/main.cpp`), not in this library.

## Upstream Source

The library fetches upstream RocksDB automatically during build from:

- `https://github.com/facebook/rocksdb/archive/refs/tags/v11.1.1.tar.gz`

No local `LIBROCKSDB_UPSTREAM` checkout path is required.

## Notes

- `snapshot_checker_compat.cc` is kept as a compatibility shim required by this
  Unikraft build configuration.
- `src/env/unique_id_gen.cc` is a local override used by this port.
