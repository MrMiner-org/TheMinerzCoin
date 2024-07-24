// Copyright (c) 2017 The Bitcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "config.h"
#include "chainparams.h"
#include "consensus/consensus.h"

GlobalConfig::GlobalConfig() : useCashAddr(false) {}
const CChainParams &GlobalConfig::GetChainParams() const { return Params(); }
static GlobalConfig gConfig;

std::string GetArg(const std::string& strArg, const std::string& strDefault)
{
    // Retrieve the argument value from configuration or command line
    // This is a placeholder for actual implementation
    if (mapArgs.count(strArg))
        return mapArgs[strArg];
    return strDefault;
}

const Config &GetConfig() { return gConfig; }
void GlobalConfig::SetCashAddrEncoding(bool c) { useCashAddr = c; }
bool GlobalConfig::UseCashAddrEncoding() const { return useCashAddr; }
const CChainParams &DummyConfig::GetChainParams() const { return Params(CBaseChainParams::REGTEST); }
