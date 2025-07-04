#include <node/utxo_snapshot.h>
#include <validation.h>
#include <test/test_bitcoin.h>
#include <boost/test/unit_test.hpp>

BOOST_FIXTURE_TEST_SUITE(assumeutxo_tests, BasicTestingSetup)

BOOST_AUTO_TEST_CASE(load_snapshot_success)
{
    fs::path temp = fs::temp_directory_path() / "utxo_snapshot.dat";
    {
        FILE* f = fopen(temp.string().c_str(), "wb");
        AutoFile af{f, SER_DISK, CLIENT_VERSION};
        node::SnapshotMetadata meta{Params().MessageStart(), uint256(), 0};
        af << meta;
    }
    BOOST_CHECK(LoadAssumeutxoSnapshot(temp.string()));
    fs::remove(temp);
}

BOOST_AUTO_TEST_CASE(load_snapshot_missing)
{
    BOOST_CHECK(!LoadAssumeutxoSnapshot("nonexistent_snapshot.dat"));
}

BOOST_AUTO_TEST_SUITE_END()
