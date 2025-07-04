#pragma once

#include <memory>
#include <string>

#ifdef ENABLE_LIGHTNING
#include <grpcpp/grpcpp.h>
#include <lnrpc/lightning.grpc.pb.h>
#endif

class LightningClient
{
public:
    explicit LightningClient(const std::string& server_uri);
    bool openChannel(const std::string& pubkey, uint64_t amount, std::string& error);
    bool closeChannel(const std::string& channel_point, std::string& error);
    bool fundChannel(const std::string& pubkey, uint64_t amount, std::string& txid, std::string& error);
private:
#ifdef ENABLE_LIGHTNING
    std::unique_ptr<lnrpc::Lightning::Stub> m_stub;
#endif
};
