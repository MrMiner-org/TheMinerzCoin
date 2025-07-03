#pragma once
#include <primitives/transaction.h>
namespace Consensus {
bool VerifyTaprootSpend(const CTransaction& tx);
}
