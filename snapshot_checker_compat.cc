#include "db/snapshot_checker.h"

namespace ROCKSDB_NAMESPACE {

DisableGCSnapshotChecker* DisableGCSnapshotChecker::Instance()
{
	static DisableGCSnapshotChecker instance;
	return &instance;
}

bool DataIsDefinitelyInSnapshot(SequenceNumber seqno, SequenceNumber snapshot,
				const SnapshotChecker* snapshot_checker)
{
	return ((seqno) <= (snapshot) &&
		(snapshot_checker == nullptr ||
		 snapshot_checker->CheckInSnapshot(seqno, snapshot) ==
			 SnapshotCheckerResult::kInSnapshot));
}

bool DataIsDefinitelyNotInSnapshot(SequenceNumber seqno,
				   SequenceNumber snapshot,
				   const SnapshotChecker* snapshot_checker)
{
	return ((seqno) > (snapshot) ||
		(snapshot_checker != nullptr &&
		 snapshot_checker->CheckInSnapshot(seqno, snapshot) ==
			 SnapshotCheckerResult::kNotInSnapshot));
}

} /* namespace ROCKSDB_NAMESPACE */
