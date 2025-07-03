#include "schnorr.h"
#include <crypto/sha256.h>

namespace crypto {
std::array<unsigned char,64> SchnorrSign(std::span<const unsigned char,32> msg, std::span<const unsigned char,32> seckey)
{
    std::array<unsigned char,64> sig{};
    // Placeholder Schnorr sign: hash msg||seckey
    CHash256 h;
    h.Write(msg.data(), msg.size());
    h.Write(seckey.data(), seckey.size());
    h.Finalize(sig.data());
    return sig;
}

bool SchnorrVerify(std::span<const unsigned char,32> msg, std::span<const unsigned char,32> pubkey, std::span<const unsigned char,64> sig)
{
    // Placeholder verify: recompute and compare
    CHash256 h;
    h.Write(msg.data(), msg.size());
    h.Write(pubkey.data(), pubkey.size());
    unsigned char expect[64];
    h.Finalize(expect);
    return std::equal(sig.data(), sig.data()+64, expect);
}
}
