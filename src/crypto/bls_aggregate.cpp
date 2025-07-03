#include "bls_aggregate.h"
#include <cstring>

namespace bls {
Signature Aggregate(const std::vector<Signature>& sigs)
{
    Signature out{};
    for (const auto& s : sigs) {
        for (size_t i = 0; i < out.data.size(); ++i) {
            out.data[i] ^= s.data[i];
        }
    }
    return out;
}
}
