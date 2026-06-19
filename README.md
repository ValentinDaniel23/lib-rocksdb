# RocksDB for Unikraft
This is the port of RocksDB for Unikraft as an external library.

## Build
RocksDB depends on the following libraries, that need to be added to
`Makefile` in this order:

* `libcxxabi`, e.g. `lib-libcxxabi`
* `libcxx`, e.g. `lib-libcxx`
* `libunwind`, e.g. `lib-libunwind`
* `compiler-rt`, e.g. `lib-compiler-rt`
* `libc`, e.g. `musl`

The upstream RocksDB sources are fetched automatically during build; no local
checkout is required.

A validation suite (the upstream RocksDB examples) is bundled in this library
and gated behind configuration, similar to the `main()` glue in `lib-sqlite`:

* `LIBROCKSDB` only — builds the library.
* `LIBROCKSDBTEST` (plus `LIBROCKSDBTEST_ALL` or individual examples) — also
  builds the validation suite, exposed via `rocksdb_test_main()`.

Application entrypoints belong in apps (for example
`catalog-core/rocksdb/main.cpp`), not in this library.

## Root filesystem

To create, import or export databases, it is necessary to have a filesystem.
The steps for creating and using a filesystem are the same as the ones used for
[nginx](https://github.com/unikraft/lib-nginx/blob/staging/README.md).

## Port notes

* `src/env/unique_id_gen.cc` is a local override used by this port to keep
  unique-id generation robust when random device access can throw.
* The build disables assertions (`NDEBUG`) for runtime stability on constrained
  targets.
* The port uses the default C++ thread integration (`CXX_THREADS`).

## Further information
Please refer to the `README.md` as well as the documentation in the
`doc/` subdirectory of the main Unikraft repository.
