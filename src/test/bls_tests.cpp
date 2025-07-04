#include <boost/test/unit_test.hpp>
#include "test/test_bitcoin.h"
#include <crypto/bls_aggregate.h>
#include <blst.h>

BOOST_FIXTURE_TEST_SUITE(bls_tests, BasicTestingSetup)

static const char DST[] = "BLS_SIG_BLS12381G2_XMD:SHA-256_SSWU_RO_NUL_";

BOOST_AUTO_TEST_CASE(aggregate_valid)
{
    // message to sign
    const unsigned char msg[4] = {1,2,3,4};

    // secret keys 1 and 2
    blst_scalar sk1, sk2;
    const uint64_t one[4] = {1,0,0,0};
    const uint64_t two[4] = {2,0,0,0};
    blst_scalar_from_uint64(&sk1, one);
    blst_scalar_from_uint64(&sk2, two);

    // public keys
    blst_p1 pk1, pk2;
    blst_sk_to_pk_in_g1(&pk1, &sk1);
    blst_sk_to_pk_in_g1(&pk2, &sk2);

    // aggregate public key
    blst_p1 pk_sum;
    blst_p1_add_or_double(&pk_sum, &pk1, &pk2);
    blst_p1_affine pk_sum_aff;
    blst_p1_to_affine(&pk_sum_aff, &pk_sum);

    // hash message
    blst_p2 hash;
    blst_hash_to_g2(&hash, msg, sizeof(msg), (const byte*)DST, sizeof(DST)-1, nullptr, 0);

    // signatures
    blst_p2 sig1, sig2;
    blst_sign_pk_in_g1(&sig1, &hash, &sk1);
    blst_sign_pk_in_g1(&sig2, &hash, &sk2);
    blst_p2_affine sig1_aff, sig2_aff;
    blst_p2_to_affine(&sig1_aff, &sig1);
    blst_p2_to_affine(&sig2_aff, &sig2);

    bls::Signature s1, s2;
    blst_p2_affine_compress(s1.data.data(), &sig1_aff);
    blst_p2_affine_compress(s2.data.data(), &sig2_aff);

    auto agg = bls::Aggregate({s1,s2});
    BOOST_CHECK(agg.has_value());

    blst_p2_affine agg_aff;
    BLST_ERROR e = blst_p2_uncompress(&agg_aff, agg->data.data());
    BOOST_CHECK(e == BLST_SUCCESS);

    BLST_ERROR verify = blst_core_verify_pk_in_g1(&pk_sum_aff, &agg_aff, true,
                                                  msg, sizeof(msg), (const byte*)DST,
                                                  sizeof(DST)-1, nullptr, 0);
    BOOST_CHECK(verify == BLST_SUCCESS);
}

BOOST_AUTO_TEST_CASE(aggregate_invalid)
{
    bls::Signature bad{}; // all zeros is invalid
    auto agg = bls::Aggregate({bad});
    BOOST_CHECK(!agg.has_value());
}

BOOST_AUTO_TEST_CASE(aggregate_empty)
{
    auto agg = bls::Aggregate({});
    BOOST_CHECK(!agg.has_value());
}

BOOST_AUTO_TEST_CASE(aggregate_three)
{
    const unsigned char msg[1] = {9};
    blst_scalar sk1, sk2, sk3;
    const uint64_t one[4] = {1,0,0,0};
    const uint64_t two[4] = {2,0,0,0};
    const uint64_t three[4] = {3,0,0,0};
    blst_scalar_from_uint64(&sk1, one);
    blst_scalar_from_uint64(&sk2, two);
    blst_scalar_from_uint64(&sk3, three);

    blst_p1 pk1, pk2, pk3;
    blst_sk_to_pk_in_g1(&pk1, &sk1);
    blst_sk_to_pk_in_g1(&pk2, &sk2);
    blst_sk_to_pk_in_g1(&pk3, &sk3);

    blst_p1 pk_sum12;
    blst_p1_add_or_double(&pk_sum12, &pk1, &pk2);
    blst_p1 pk_sum;
    blst_p1_add_or_double(&pk_sum, &pk_sum12, &pk3);
    blst_p1_affine pk_sum_aff;
    blst_p1_to_affine(&pk_sum_aff, &pk_sum);

    blst_p2 hash;
    blst_hash_to_g2(&hash, msg, sizeof(msg), (const byte*)DST, sizeof(DST)-1, nullptr, 0);

    blst_p2 sig1, sig2, sig3;
    blst_sign_pk_in_g1(&sig1, &hash, &sk1);
    blst_sign_pk_in_g1(&sig2, &hash, &sk2);
    blst_sign_pk_in_g1(&sig3, &hash, &sk3);
    blst_p2_affine sig1_aff, sig2_aff, sig3_aff;
    blst_p2_to_affine(&sig1_aff, &sig1);
    blst_p2_to_affine(&sig2_aff, &sig2);
    blst_p2_to_affine(&sig3_aff, &sig3);

    bls::Signature s1, s2, s3;
    blst_p2_affine_compress(s1.data.data(), &sig1_aff);
    blst_p2_affine_compress(s2.data.data(), &sig2_aff);
    blst_p2_affine_compress(s3.data.data(), &sig3_aff);

    auto agg = bls::Aggregate({s1, s2, s3});
    BOOST_REQUIRE(agg.has_value());

    blst_p2_affine agg_aff;
    BLST_ERROR e = blst_p2_uncompress(&agg_aff, agg->data.data());
    BOOST_REQUIRE(e == BLST_SUCCESS);

    BLST_ERROR verify = blst_core_verify_pk_in_g1(&pk_sum_aff, &agg_aff, true,
                                                  msg, sizeof(msg), (const byte*)DST,
                                                  sizeof(DST)-1, nullptr, 0);
    BOOST_CHECK(verify == BLST_SUCCESS);
}

BOOST_AUTO_TEST_SUITE_END()
