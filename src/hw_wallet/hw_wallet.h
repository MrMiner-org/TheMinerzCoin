#ifndef BITCOIN_HW_WALLET_H
#define BITCOIN_HW_WALLET_H

#include <string>
#include <vector>

struct HWDeviceInfo {
    unsigned short vendor_id;
    unsigned short product_id;
    std::string path;
    std::string manufacturer;
    std::string product;
    std::string serial;
};

std::vector<HWDeviceInfo> EnumerateHardwareWallets();
bool SendToHardwareWallet(const std::string& path, const std::vector<unsigned char>& data, std::string& err);

#endif // BITCOIN_HW_WALLET_H
