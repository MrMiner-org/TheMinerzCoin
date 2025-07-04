#include "neutrino/compact_filter.h"
#include "hash.h"

CompactFilter::CompactFilter(uint8_t key, const std::vector<unsigned char>& filter)
    : m_key(key), m_filter(filter) {}

bool CompactFilter::Match(const std::vector<unsigned char>& element) const
{
    // Very small simplified matching using first byte of the double SHA256 hash
    uint256 h = Hash(element.begin(), element.end());
    unsigned char prefix = h.begin()[0] ^ m_key;
    for (unsigned char b : m_filter) {
        if (b == prefix) return true;
    }
    return false;
}
