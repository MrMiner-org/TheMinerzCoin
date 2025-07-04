#include "hw_wallet.h"
#ifdef HAVE_HIDAPI
#include <hidapi/hidapi.h>
#endif

#include <string>
#include <vector>
#include <locale>
#include <codecvt>

std::vector<HWDeviceInfo> EnumerateHardwareWallets()
{
    std::vector<HWDeviceInfo> devices;
#ifdef HAVE_HIDAPI
    if (hid_init() != 0)
        return devices;

    struct hid_device_info* devs = hid_enumerate(0x0, 0x0);
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    for (struct hid_device_info* cur = devs; cur; cur = cur->next) {
        HWDeviceInfo info;
        info.vendor_id = cur->vendor_id;
        info.product_id = cur->product_id;
        if (cur->path)
            info.path = cur->path;
        if (cur->manufacturer_string)
            info.manufacturer = conv.to_bytes(cur->manufacturer_string);
        if (cur->product_string)
            info.product = conv.to_bytes(cur->product_string);
        if (cur->serial_number)
            info.serial = conv.to_bytes(cur->serial_number);
        devices.push_back(info);
    }
    hid_free_enumeration(devs);
    hid_exit();
#endif
    return devices;
}

bool SendToHardwareWallet(const std::string& path, const std::vector<unsigned char>& data, std::string& err)
{
#ifdef HAVE_HIDAPI
    hid_device* handle = hid_open_path(path.c_str());
    if (!handle) {
        err = "open failed";
        return false;
    }
    int res = hid_write(handle, data.data(), data.size());
    hid_close(handle);
    if (res < 0) {
        err = "write failed";
        return false;
    }
    return true;
#else
    err = "hidapi not available";
    return false;
#endif
}
