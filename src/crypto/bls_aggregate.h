#pragma once
#include <array>
#include <vector>
#include <optional>

namespace bls {
struct Signature {
    std::array<unsigned char,96> data{}; // BLS12-381 signature size
};

/** Aggregate multiple BLS signatures.
 *  Returns std::nullopt if any signature fails to deserialize. */
std::optional<Signature> Aggregate(const std::vector<Signature>& sigs);
}
