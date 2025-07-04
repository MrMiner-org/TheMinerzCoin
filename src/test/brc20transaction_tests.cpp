#include <primitives/brc20transaction.h>
#include <boost/test/unit_test.hpp>
#include <test/test_bitcoin.h>

bool ValidateTransaction(const CTransaction& tx);

BOOST_FIXTURE_TEST_SUITE(brc20_transaction_tests, BasicTestingSetup)

BOOST_AUTO_TEST_CASE(brc20_validate_basic)
{
    CMutableBRC20Transaction mut;
    mut.tokenType = "TEST";
    mut.amount = 10;
    CBRC20Transaction tx(mut);

    BOOST_CHECK(ValidateTransaction(tx));

    mut.amount = 0;
    CBRC20Transaction bad(mut);
    BOOST_CHECK(!ValidateTransaction(bad));
}

BOOST_AUTO_TEST_SUITE_END()
