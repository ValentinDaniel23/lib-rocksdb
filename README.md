# lib-rocksdb

Unikraft port of RocksDB.

This port expects an existing RocksDB upstream source tree and builds it as a
Unikraft library.

## Upstream Source

Set `LIBROCKSDB_UPSTREAM` to point to the RocksDB source tree (the directory
containing `include/`, `db/`, `table/`, etc.).

The `catalog-core/rocksdb` application in this thesis workspace wires this up
by passing `LIBROCKSDB_UPSTREAM=$(PWD)/../../repos/rocksdb` to the Unikraft
build.

## Minimal Usage

Enable:

- `Library Configuration` -> `RocksDB` -> `Provide main function` (optional)

Then build a `catalog-core` application that selects `LIBROCKSDB`.
