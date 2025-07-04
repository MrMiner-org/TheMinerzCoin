#include "wallet/psbt.h"
#include "utilstrencodings.h"
#include <vector>

std::string EncodePsbtV2(const CMutableTransaction& tx)
{
    CDataStream ss(SER_NETWORK, PROTOCOL_VERSION);
    ss << tx;
    std::string raw(ss.begin(), ss.end());
    return "psbtv2:" + EncodeBase64(raw);
}

bool DecodePsbtV2(const std::string& psbt, CMutableTransaction& tx)
{
    const std::string prefix = "psbtv2:";
    if (psbt.rfind(prefix, 0) != 0) return false;
    std::vector<unsigned char> data = DecodeBase64(psbt.substr(prefix.size()).c_str());
    CDataStream ss(data, SER_NETWORK, PROTOCOL_VERSION);
    try {
        ss >> tx;
    } catch (...) {
        return false;
    }
    return true;
}
