#include "primitives/block.h"
#include "streams.h"
#include "version.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    try {
        CDataStream stream((const char*)data, (const char*)data + size, SER_NETWORK, PROTOCOL_VERSION);
        CBlock block;
        stream >> block;
    } catch (const std::exception&) {
        // ignore deserialization errors
    }
    return 0;
}
