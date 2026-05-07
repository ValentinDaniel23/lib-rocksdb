#include <rocksdb/db.h>
#include <rocksdb/options.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <sys/stat.h>
#include <sys/types.h>

#include <memory>

#include <uk/print.h>

static void usage(const char* prog)
{
	uk_pr_info("Usage: %s [db_path] [key] [value]\n", prog);
	uk_pr_info("Defaults: db_path=/data/rocksdb key=hello value=unikraft\n");
}

static void ensure_dir(const char* path)
{
	/* Best-effort: if mkdir fails because it exists, ignore. */
	(void)mkdir(path, 0755);
}

int main(int argc, char** argv)
{
	const char* db_path = "/data/rocksdb";
	const char* key = "hello";
	const char* value = "unikraft";

	if (argc > 1 && (std::strcmp(argv[1], "-h") == 0 || std::strcmp(argv[1], "--help") == 0)) {
		usage(argv[0]);
		return 0;
	}
	if (argc > 1) {
		db_path = argv[1];
	}
	if (argc > 2) {
		key = argv[2];
	}
	if (argc > 3) {
		value = argv[3];
	}

	/* Create a common parent directory in the default case. */
	if (std::strncmp(db_path, "/data", 5) == 0) {
		ensure_dir("/data");
	}

	rocksdb::Options options;
	options.create_if_missing = true;

	std::unique_ptr<rocksdb::DB> db;
	uk_pr_info("rocksdb: opening %s\n", db_path);
	rocksdb::Status status = rocksdb::DB::Open(options, db_path, &db);
	if (!status.ok()) {
		uk_pr_err("rocksdb: open failed: %s\n", status.ToString().c_str());
		return 1;
	}

	status = db->Put(rocksdb::WriteOptions(), key, value);
	if (!status.ok()) {
		uk_pr_err("rocksdb: put failed: %s\n", status.ToString().c_str());
		return 1;
	}

	std::string read_value;
	status = db->Get(rocksdb::ReadOptions(), key, &read_value);
	if (!status.ok()) {
		uk_pr_err("rocksdb: get failed: %s\n", status.ToString().c_str());
		return 1;
	}

	uk_pr_info("rocksdb: %s=%s\n", key, read_value.c_str());
	return 0;
}
