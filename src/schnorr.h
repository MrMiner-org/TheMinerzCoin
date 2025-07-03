#pragma once

#include <array>
#include <span>

/** BIP340 Schnorr signing and verification helpers. */
namespace crypto {

//! Sign a 32-byte message using a 32-byte secret key producing a 64-byte signature.
std::array<unsigned char,64> SchnorrSign(std::span<const unsigned char,32> msg,
                                         std::span<const unsigned char,32> seckey);

//! Verify a Schnorr signature against a 32-byte message and x-only public key.
bool SchnorrVerify(std::span<const unsigned char,32> msg,
                   std::span<const unsigned char,32> pubkey,
                   std::span<const unsigned char,64> sig);

} // namespace crypto
