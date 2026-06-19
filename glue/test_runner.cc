#include <cstdio>
#include <sys/stat.h>
#include <sys/types.h>

#include "rocksdb/db.h"
#include "rocksdb/options.h"
#include "test_runner.h"

/* Forward declarations for renamed example functions (applied by the patch). */

#if defined(CONFIG_LIBROCKSDBTEST_ALL) || defined(CONFIG_LIBROCKSDBTEST_SIMPLE)
extern int simple_example_main(int argc, char** argv);
#endif

#if defined(CONFIG_LIBROCKSDBTEST_ALL) || defined(CONFIG_LIBROCKSDBTEST_C_SIMPLE)
extern "C" int c_simple_example_main(int argc, char** argv);
#endif

#if defined(CONFIG_LIBROCKSDBTEST_ALL) || defined(CONFIG_LIBROCKSDBTEST_COLUMN_FAMILIES)
extern int column_families_example_main(int argc, char** argv);
#endif

#if defined(CONFIG_LIBROCKSDBTEST_ALL) || defined(CONFIG_LIBROCKSDBTEST_COMPACT_FILES)
extern int compact_files_example_main(int argc, char** argv);
#endif

#if defined(CONFIG_LIBROCKSDBTEST_ALL) || defined(CONFIG_LIBROCKSDBTEST_COMPACTION_FILTER)
extern int compaction_filter_example_main(int argc, char** argv);
#endif

#if defined(CONFIG_LIBROCKSDBTEST_ALL) || defined(CONFIG_LIBROCKSDBTEST_TRANSACTIONS)
extern int transaction_example_main(int argc, char** argv);
#endif

#if defined(CONFIG_LIBROCKSDBTEST_ALL) || defined(CONFIG_LIBROCKSDBTEST_OPTIMISTIC_TRANSACTIONS)
extern int optimistic_transaction_example_main(int argc, char** argv);
#endif

#if defined(CONFIG_LIBROCKSDBTEST_ALL) || defined(CONFIG_LIBROCKSDBTEST_OPTIONS_FILE)
extern int options_file_example_main(int argc, char** argv);
#endif

/* -------------------------------------------------------------------------
 * Helpers
 * ---------------------------------------------------------------------- */

static void cleanup_db_dirs()
{
	ROCKSDB_NAMESPACE::Options opts;
	ROCKSDB_NAMESPACE::DestroyDB("/tmp/rocksdb_simple_example",        opts);
	ROCKSDB_NAMESPACE::DestroyDB("/tmp/rocksdb_c_simple_example",      opts);
	ROCKSDB_NAMESPACE::DestroyDB("/tmp/rocksdb_c_simple_example_backup", opts);
	ROCKSDB_NAMESPACE::DestroyDB("/tmp/rocksdb_column_families_example", opts);
	ROCKSDB_NAMESPACE::DestroyDB("/tmp/rocksdb_compact_files_example", opts);
	ROCKSDB_NAMESPACE::DestroyDB("/tmp/rocksmergetest",                opts);
	ROCKSDB_NAMESPACE::DestroyDB("/tmp/rocksdb_transaction_example",   opts);
	ROCKSDB_NAMESPACE::DestroyDB("/tmp/rocksdb_options_file_example",  opts);
}

/* -------------------------------------------------------------------------
 * Test table
 * ---------------------------------------------------------------------- */

struct TestEntry {
	const char* name;
	int (*func)(int, char**);
};

/* -------------------------------------------------------------------------
 * Public entry point
 * ---------------------------------------------------------------------- */

extern "C" int rocksdb_test_main(void)
{
	/* Ensure /tmp exists — ramfs root may not have it pre-created. */
	mkdir("/tmp", 0755);

	TestEntry tests[] = {
#if defined(CONFIG_LIBROCKSDBTEST_ALL) || defined(CONFIG_LIBROCKSDBTEST_SIMPLE)
		{ "simple_example",
		  simple_example_main },
#endif
#if defined(CONFIG_LIBROCKSDBTEST_ALL) || defined(CONFIG_LIBROCKSDBTEST_C_SIMPLE)
		{ "c_simple_example",
		  [](int a, char** v) { return c_simple_example_main(a, v); } },
#endif
#if defined(CONFIG_LIBROCKSDBTEST_ALL) || defined(CONFIG_LIBROCKSDBTEST_COLUMN_FAMILIES)
		{ "column_families_example",
		  column_families_example_main },
#endif
#if defined(CONFIG_LIBROCKSDBTEST_ALL) || defined(CONFIG_LIBROCKSDBTEST_COMPACT_FILES)
		{ "compact_files_example",
		  compact_files_example_main },
#endif
#if defined(CONFIG_LIBROCKSDBTEST_ALL) || defined(CONFIG_LIBROCKSDBTEST_COMPACTION_FILTER)
		{ "compaction_filter_example",
		  compaction_filter_example_main },
#endif
#if defined(CONFIG_LIBROCKSDBTEST_ALL) || defined(CONFIG_LIBROCKSDBTEST_TRANSACTIONS)
		{ "transaction_example",
		  transaction_example_main },
#endif
#if defined(CONFIG_LIBROCKSDBTEST_ALL) || defined(CONFIG_LIBROCKSDBTEST_OPTIMISTIC_TRANSACTIONS)
		{ "optimistic_transaction_example",
		  optimistic_transaction_example_main },
#endif
#if defined(CONFIG_LIBROCKSDBTEST_ALL) || defined(CONFIG_LIBROCKSDBTEST_OPTIONS_FILE)
		{ "options_file_example",
		  options_file_example_main },
#endif
	};

	int total  = (int)(sizeof(tests) / sizeof(tests[0]));
	int passed = 0;
	int failed = 0;

	printf("=== RocksDB Unikraft Test Suite ===\n");
	printf("Running %d test(s)\n\n", total);

	for (int i = 0; i < total; i++) {
		printf("[%d/%d] %-42s ... ", i + 1, total, tests[i].name);
		fflush(stdout);

		cleanup_db_dirs();
		int rc = tests[i].func(0, nullptr);

		if (rc == 0) {
			printf("OK\n");
			passed++;
		} else {
			printf("FAIL (exit code %d)\n", rc);
			failed++;
		}
	}

	printf("\n=== Summary: %d passed, %d failed out of %d ===\n",
	       passed, failed, total);
	return failed;
}
