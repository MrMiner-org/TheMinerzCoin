#include "script/interpreter.h"
#include "script/script.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    size_t half = size / 2;
    CScript scriptSig(data, data + half);
    CScript scriptPubKey(data + half, data + size);
    ScriptError err;
    BaseSignatureChecker checker;
    VerifyScript(scriptSig, scriptPubKey, SCRIPT_VERIFY_NONE, checker, &err);
    return 0;
}
