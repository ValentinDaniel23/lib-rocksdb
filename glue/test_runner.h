#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Run the RocksDB validation suite.
 *
 * Executes every upstream example that was compiled in via Config.uk.
 * Returns 0 if all tests pass, or the count of failed tests.
 * Call this from your application's main().
 */
int rocksdb_test_main(void);

#ifdef __cplusplus
}
#endif
