#include "slashing.h"
#include "utiltime.h"
#include "utilstrencodings.h"
#include <map>

namespace Consensus {

static std::map<CKeyID, std::map<int64_t, uint256>> mapValidatorBlocks;
static std::map<CKeyID, ValidatorStatus> mapValidatorStatus;

static void SlashValidator(const CKeyID& validator, const char* reason)
{
    ValidatorStatus& st = mapValidatorStatus[validator];
    CAmount penalty = st.stake / 10; // simple 10% penalty
    st.stake -= penalty;
    st.slashed += penalty;
}

void ReportValidatorBlock(const CKeyID& validator, int64_t height, const uint256& hash)
{
    ValidatorStatus& st = mapValidatorStatus[validator];
    st.lastBlockTime = GetTime();

    std::map<int64_t, uint256>& byHeight = mapValidatorBlocks[validator];
    auto it = byHeight.find(height);
    if (it != byHeight.end() && it->second != hash) {
        SlashValidator(validator, "equivocation");
    }
    byHeight[height] = hash;
}

void CheckOfflineValidators(int64_t currentTime, int64_t offlineThreshold)
{
    for (auto& item : mapValidatorStatus) {
        if (currentTime - item.second.lastBlockTime > offlineThreshold) {
            SlashValidator(item.first, "offline");
            item.second.lastBlockTime = currentTime;
        }
    }
}

UniValue GetSlashingInfo()
{
    UniValue result(UniValue::VARR);
    for (const auto& it : mapValidatorStatus) {
        UniValue obj(UniValue::VOBJ);
        obj.pushKV("validator", HexStr(it.first.begin(), it.first.end()));
        obj.pushKV("stake", it.second.stake);
        obj.pushKV("slashed", it.second.slashed);
        result.push_back(obj);
    }
    return result;
}

} // namespace Consensus
