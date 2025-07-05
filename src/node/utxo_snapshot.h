#ifndef BITCOIN_NODE_UTXO_SNAPSHOT_H
#define BITCOIN_NODE_UTXO_SNAPSHOT_H

#include <chainparams.h>
#include <serialize.h>
#include <uint256.h>
#include <fs.h>
#include <util/chaintype.h>
#include <set>
#include <optional>
#include <string_view>

static constexpr std::array<uint8_t,5> SNAPSHOT_MAGIC_BYTES = {'u','t','x','o',0xff};

class Chainstate;

namespace node {

class SnapshotMetadata
{
    inline static const uint16_t VERSION{2};
    const std::set<uint16_t> m_supported_versions{VERSION};
    const MessageStartChars m_network_magic;
public:
    uint256 m_base_blockhash;
    uint64_t m_coins_count{0};

    SnapshotMetadata(const MessageStartChars magic) : m_network_magic(magic) {}
    SnapshotMetadata(const MessageStartChars magic, const uint256& base, uint64_t coins)
        : m_network_magic(magic), m_base_blockhash(base), m_coins_count(coins) {}

    template <typename Stream>
    void Serialize(Stream& s) const
    {
        s << SNAPSHOT_MAGIC_BYTES;
        s << VERSION;
        s << m_network_magic;
        s << m_base_blockhash;
        s << m_coins_count;
    }
    template <typename Stream>
    void Unserialize(Stream& s)
    {
        std::array<uint8_t, SNAPSHOT_MAGIC_BYTES.size()> magic;
        s >> magic;
        if (magic != SNAPSHOT_MAGIC_BYTES) {
            throw std::ios_base::failure("Invalid UTXO set snapshot magic bytes.");
        }
        uint16_t version;
        s >> version;
        if (m_supported_versions.count(version) == 0) {
            throw std::ios_base::failure("Version of snapshot does not match supported versions.");
        }
        MessageStartChars message;
        s >> message;
        if (!std::equal(message.begin(), message.end(), m_network_magic.data())) {
            throw std::ios_base::failure("Snapshot network mismatch");
        }
        s >> m_base_blockhash;
        s >> m_coins_count;
    }
};

const fs::path SNAPSHOT_BLOCKHASH_FILENAME{"base_blockhash"};
constexpr std::string_view SNAPSHOT_CHAINSTATE_SUFFIX{"_snapshot"};

bool WriteSnapshotBaseBlockhash(Chainstate& snapshot_chainstate);
std::optional<uint256> ReadSnapshotBaseBlockhash(fs::path chaindir);
std::optional<fs::path> FindSnapshotChainstateDir(const fs::path& data_dir);

} // namespace node

#endif // BITCOIN_NODE_UTXO_SNAPSHOT_H
