#include <boost/test/unit_test.hpp>
#include "test/test_bitcoin.h"
#include <wallet/wallet.h>
#include <consensus/taproot.h>
#include <script/interpreter.h>
#include <script/script.h>

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

BOOST_AUTO_TEST_CASE(taproot_element_size_limit)
{
    std::vector<unsigned char> data(MAX_TAPROOT_SCRIPT_ELEMENT_SIZE, 'x');
    CScript script;
    script << data;
    std::vector<std::vector<unsigned char>> stack;
    ScriptError err;
    BOOST_CHECK(EvalScript(stack, script, SCRIPT_VERIFY_TAPROOT, BaseSignatureChecker(), &err));
    BOOST_CHECK(err == SCRIPT_ERR_OK);

    data.push_back('y');
    script.clear();
    script << data;
    stack.clear();
    BOOST_CHECK(!EvalScript(stack, script, SCRIPT_VERIFY_TAPROOT, BaseSignatureChecker(), &err));
    BOOST_CHECK(err == SCRIPT_ERR_PUSH_SIZE);
}

BOOST_AUTO_TEST_SUITE_END()
