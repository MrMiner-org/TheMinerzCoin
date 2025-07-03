#pragma once
#include <array>
#include <span>
namespace crypto {
std::array<unsigned char,64> SchnorrSign(std::span<const unsigned char,32> msg, std::span<const unsigned char,32> seckey);
bool SchnorrVerify(std::span<const unsigned char,32> msg, std::span<const unsigned char,32> pubkey, std::span<const unsigned char,64> sig);
}
