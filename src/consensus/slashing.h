#ifndef BITCOIN_CONSENSUS_SLASHING_H
#define BITCOIN_CONSENSUS_SLASHING_H

#include "amount.h"
#include "pubkey.h"
#include <map>
#include <stdint.h>
#include <string>
#include <univalue.h>
#include <uint256.h>

namespace Consensus {

struct ValidatorStatus {
    CAmount stake;
    int64_t lastBlockTime;
    CAmount slashed;
    ValidatorStatus() : stake(0), lastBlockTime(0), slashed(0) {}
};

void ReportValidatorBlock(const CKeyID& validator, int64_t height, const uint256& hash);
void CheckOfflineValidators(int64_t currentTime, int64_t offlineThreshold);
UniValue GetSlashingInfo();

} // namespace Consensus

#endif // BITCOIN_CONSENSUS_SLASHING_H
