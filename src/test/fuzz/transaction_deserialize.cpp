#include "primitives/transaction.h"
#include "streams.h"
#include "version.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    try {
        CDataStream stream((const char*)data, (const char*)data + size, SER_NETWORK, PROTOCOL_VERSION);
        CTransaction tx;
        stream >> tx;
    } catch (const std::exception&) {
        // ignore deserialization errors
    }
    return 0;
}
