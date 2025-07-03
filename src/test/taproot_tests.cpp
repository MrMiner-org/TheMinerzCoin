#include <boost/test/unit_test.hpp>
#include "test/test_bitcoin.h"
#include <wallet/wallet.h>
#include <consensus/taproot.h>

BOOST_FIXTURE_TEST_SUITE(taproot_tests, BasicTestingSetup)

BOOST_AUTO_TEST_CASE(create_sign_verify)
{
    CKey key;
    key.MakeNewKey(true);
    CTxOut out;
    CWallet wallet;
    BOOST_CHECK(wallet.CreateTaprootOutput(key, out));
    BOOST_CHECK(out.scriptPubKey.size() == 34);

    CMutableTransaction tx;
    tx.vin.resize(1);
    tx.vout.push_back(out);

    BOOST_CHECK(wallet.SignTransactionSchnorr(tx, key));
    CTransaction ctx(tx);
    BOOST_CHECK(Consensus::VerifyTaprootSpend(ctx));
}

BOOST_AUTO_TEST_SUITE_END()
