#include "lightning_client.h"

#ifdef ENABLE_LIGHTNING
#include <grpcpp/create_channel.h>
#include <grpcpp/client_context.h>
#include <lnrpc/lightning.pb.h>

LightningClient::LightningClient(const std::string& uri)
    : m_stub(lnrpc::Lightning::NewStub(grpc::CreateChannel(uri, grpc::InsecureChannelCredentials()))) {}

bool LightningClient::openChannel(const std::string& pubkey, uint64_t amount, std::string& error)
{
    lnrpc::OpenChannelRequest req;
    req.set_node_pubkey_string(pubkey);
    req.set_local_funding_amount(amount);

    lnrpc::ChannelPoint resp;
    grpc::ClientContext ctx;
    auto status = m_stub->OpenChannelSync(&ctx, req, &resp);
    if (!status.ok()) {
        error = status.error_message();
        return false;
    }
    return true;
}

bool LightningClient::closeChannel(const std::string& cp, std::string& error)
{
    lnrpc::CloseChannelRequest req;
    req.mutable_channel_point()->set_funding_txid_str(cp);
    lnrpc::CloseStatusUpdate update;
    grpc::ClientContext ctx;
    std::unique_ptr<grpc::ClientReader<lnrpc::CloseStatusUpdate>> stream = m_stub->CloseChannel(&ctx, req);
    if (!stream->Read(&update)) {
        error = "no response";
        return false;
    }
    auto status = stream->Finish();
    if (!status.ok()) {
        error = status.error_message();
        return false;
    }
    return true;
}

bool LightningClient::fundChannel(const std::string& pubkey, uint64_t amount, std::string& txid, std::string& error)
{
    lnrpc::OpenChannelRequest req;
    req.set_node_pubkey_string(pubkey);
    req.set_local_funding_amount(amount);

    lnrpc::ChannelPoint resp;
    grpc::ClientContext ctx;
    auto status = m_stub->OpenChannelSync(&ctx, req, &resp);
    if (!status.ok()) {
        error = status.error_message();
        return false;
    }
    txid = resp.funding_txid_str();
    return true;
}

#else

LightningClient::LightningClient(const std::string&) {}

bool LightningClient::openChannel(const std::string&, uint64_t, std::string&) { return false; }

bool LightningClient::closeChannel(const std::string&, std::string&) { return false; }

bool LightningClient::fundChannel(const std::string&, uint64_t, std::string&, std::string&) { return false; }

#endif

