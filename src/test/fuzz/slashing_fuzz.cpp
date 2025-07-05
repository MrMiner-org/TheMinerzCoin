#include "consensus/slashing.h"
#include "crypto/common.h"
#include "utilstrencodings.h"
#include "utiltime.h"

#include <cassert>
#include <cstdint>
#include <map>
#include <vector>

using namespace Consensus;

struct FuzzValidator {
    CAmount stake{1000};
    int64_t lastBlockTime{0};
    CAmount slashed{0};
    std::map<int64_t, uint256> blocks;
};

static std::map<CKeyID, FuzzValidator> validators;

static void Slash(FuzzValidator& v)
{
    CAmount penalty = v.stake / 10;
    v.stake -= penalty;
    v.slashed += penalty;
    assert(v.stake >= 0);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    size_t pos = 0;
    while (pos < size) {
        uint8_t op = data[pos++];
        if (op % 2 == 0) {
            if (pos + 20 + 8 + 32 + 8 > size) break;
            std::vector<unsigned char> idBytes(data + pos, data + pos + 20);
            CKeyID id(uint160(idBytes));
            pos += 20;
            int64_t height = (int64_t)ReadLE64(data + pos);
            pos += 8;
            std::vector<unsigned char> hBytes(data + pos, data + pos + 32);
            uint256 hash(hBytes);
            pos += 32;
            int64_t time = (int64_t)ReadLE64(data + pos);
            pos += 8;

            SetMockTime(time);
            ReportValidatorBlock(id, height, hash);

            FuzzValidator& fv = validators[id];
            fv.lastBlockTime = time;
            auto it = fv.blocks.find(height);
            if (it != fv.blocks.end() && it->second != hash) {
                CAmount before = fv.slashed;
                Slash(fv);
                assert(fv.slashed > before);
            }
            fv.blocks[height] = hash;
        } else {
            if (pos + 16 > size) break;
            int64_t currentTime = (int64_t)ReadLE64(data + pos);
            pos += 8;
            int64_t threshold = (int64_t)ReadLE64(data + pos);
            pos += 8;
            if (threshold < 0) threshold = -threshold;

            SetMockTime(currentTime);
            CheckOfflineValidators(currentTime, threshold);

            for (auto& kv : validators) {
                if (currentTime - kv.second.lastBlockTime > threshold) {
                    CAmount prev = kv.second.slashed;
                    Slash(kv.second);
                    kv.second.lastBlockTime = currentTime;
                    assert(kv.second.slashed > prev);
                }
            }
        }
        for (const auto& kv : validators) {
            assert(kv.second.stake >= 0);
        }
    }
    return 0;
}
