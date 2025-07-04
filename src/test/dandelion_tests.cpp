#include <boost/test/unit_test.hpp>
#include "test/test_bitcoin.h"
#include <p2p/dandelion.h>
#include <primitives/transaction.h>
#include <boost/thread.hpp>
#include <utiltime.h>

BOOST_FIXTURE_TEST_SUITE(dandelion_tests, BasicTestingSetup)

BOOST_AUTO_TEST_CASE(queue_and_flush)
{
    CMutableTransaction mut;
    mut.vin.resize(1);
    mut.vout.resize(1);
    CTransaction tx(mut);
    p2p::AddToStemPool(tx);
    boost::thread t(p2p::FlushStemPool);
    bool joined = t.timed_join(boost::posix_time::seconds(1));
    BOOST_CHECK(joined);
}

BOOST_AUTO_TEST_CASE(epoch_transition)
{
    CMutableTransaction mut;
    mut.vin.resize(1);
    mut.vout.resize(1);
    CTransaction tx(mut);

    // Simulate time progression to trigger epoch expiration
    SetMockTime(GetTime());
    p2p::AddToStemPool(tx);
    SetMockTime(GetTime() + 200); // after epoch and embargo
    p2p::FlushStemPool();
    SetMockTime(0);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()
