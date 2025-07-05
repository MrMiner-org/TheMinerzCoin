#ifndef KERNEL_STUB_H
#define KERNEL_STUB_H
#include <optional>
#include <string>

namespace kernel {

enum class Warning { LARGE_WORK_INVALID_CHAIN, UNKNOWN_NEW_RULES_ACTIVATED };

struct CCoinsStats {};

enum class CoinStatsHashType { HASH_SERIALIZED };

class Notifications {
public:
    void warningSet(Warning, const std::string&) {}
    void warningUnset(Warning) {}
    template <typename... Args>
    bool blockTip(Args&&...) { return false; }
};

template <typename... Args>
std::optional<CCoinsStats> ComputeUTXOStats(Args&&...) {
    return CCoinsStats{};
}

inline bool IsInterrupted(bool value) { return value; }

} // namespace kernel

#endif // KERNEL_STUB_H
