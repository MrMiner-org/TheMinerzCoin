#include <boost/test/unit_test.hpp>
#include "test/test_bitcoin.h"
#include <p2p/dandelion.h>
#include <primitives/transaction.h>

BOOST_FIXTURE_TEST_SUITE(dandelion_tests, BasicTestingSetup)

BOOST_AUTO_TEST_CASE(queue_and_flush)
{
    CMutableTransaction mut;
    mut.vin.resize(1);
    mut.vout.resize(1);
    CTransaction tx(mut);
    p2p::AddToStemPool(tx);
    p2p::FlushStemPool();
    BOOST_CHECK(true); // no crash
}

BOOST_AUTO_TEST_SUITE_END()
