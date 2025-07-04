#pragma once

#include <vector>
#include <cstdint>

/** Simplified compact filter used by the Neutrino light client. */
class CompactFilter
{
public:
    CompactFilter() = default;
    CompactFilter(uint8_t key, const std::vector<unsigned char>& filter);

    //! Check if the filter likely contains the element
    bool Match(const std::vector<unsigned char>& element) const;

private:
    uint8_t m_key{0};
    std::vector<unsigned char> m_filter;
};
