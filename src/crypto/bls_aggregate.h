#pragma once
#include <array>
#include <vector>

namespace bls {
struct Signature {
    std::array<unsigned char,96> data{}; // BLS12-381 signature size
};

Signature Aggregate(const std::vector<Signature>& sigs);
}
