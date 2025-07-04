#ifndef THEMZ_ROLLUP_BLOCK_COMMITMENT_H
#define THEMZ_ROLLUP_BLOCK_COMMITMENT_H

#include <vector>
#include <span>
#include "uint256.h"

class BlockCommitment {
public:
    BlockCommitment() = default;

    /** Store a commitment for the provided rollup block data. */
    void record(std::span<const unsigned char> block_data);

    /** Return all recorded commitments (for testing). */
    const std::vector<uint256>& GetCommitments() const { return m_commitments; }

private:
    std::vector<uint256> m_commitments{};
};

#endif // THEMZ_ROLLUP_BLOCK_COMMITMENT_H
