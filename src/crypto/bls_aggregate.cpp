#include "bls_aggregate.h"
#include <blst.h>

#include <cstring>

namespace bls {
std::optional<Signature> Aggregate(const std::vector<Signature>& sigs)
{
    blst_p2 agg;
    bool first = true;

    for (const auto& s : sigs) {
        blst_p2_affine sig_aff;
        if (BLST_SUCCESS != blst_p2_uncompress(&sig_aff, s.data.data())) {
            return std::nullopt;
        }

        if (first) {
            blst_p2_from_affine(&agg, &sig_aff);
            first = false;
        } else {
            blst_p2_add_or_double_affine(&agg, &agg, &sig_aff);
        }
    }

    Signature out{};
    if (!first) {
        blst_p2_affine out_aff;
        blst_p2_to_affine(&out_aff, &agg);
        blst_p2_affine_compress(out.data.data(), &out_aff);
    }
    return out;
}
}
