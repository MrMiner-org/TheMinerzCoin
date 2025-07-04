#include "block_commitment.h"
#include "hash.h"

void BlockCommitment::record(std::span<const unsigned char> block_data)
{
    uint256 commitment = Hash(block_data.begin(), block_data.end());
    m_commitments.push_back(commitment);
}
