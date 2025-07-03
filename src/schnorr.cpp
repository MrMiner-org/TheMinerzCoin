#include "schnorr.h"
#include <crypto/sha256.h>
#include <random.h>
#include <secp256k1.h>
#include <secp256k1_schnorrsig.h>
#include <secp256k1_extrakeys.h>

namespace crypto {

namespace {
secp256k1_context* GetContext()
{
    static secp256k1_context* ctx = nullptr;
    if (!ctx) {
        ctx = secp256k1_context_create(SECP256K1_CONTEXT_SIGN | SECP256K1_CONTEXT_VERIFY);
        unsigned char seed[32];
        GetRandBytes(seed, 32);
        secp256k1_context_randomize(ctx, seed);
    }
    return ctx;
}
}

std::array<unsigned char,64> SchnorrSign(std::span<const unsigned char,32> msg,
                                         std::span<const unsigned char,32> seckey)
{
    std::array<unsigned char,64> sig{};
    secp256k1_keypair keypair;
    if (!secp256k1_keypair_create(GetContext(), &keypair, seckey.data())) {
        return sig;
    }
    if (!secp256k1_schnorrsig_sign(GetContext(), sig.data(), msg.data(), &keypair, NULL, NULL)) {
        sig.fill(0);
    }
    return sig;
}

bool SchnorrVerify(std::span<const unsigned char,32> msg,
                   std::span<const unsigned char,32> pubkey,
                   std::span<const unsigned char,64> sig)
{
    secp256k1_xonly_pubkey pk;
    if (!secp256k1_xonly_pubkey_parse(GetContext(), &pk, pubkey.data())) {
        return false;
    }
    return secp256k1_schnorrsig_verify(GetContext(), sig.data(), msg.data(), &pk);
}

} // namespace crypto
