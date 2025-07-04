#include "node_service.h"
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <memory>
#include "rpc/blockchain.h"
#include "rpc/rawtransaction.h"

static std::unique_ptr<grpc::Server> g_server;

::grpc::Status NodeServiceImpl::GetBlock(::grpc::ServerContext*, const theminerzcoin::BlockRequest* request,
                                        theminerzcoin::BlockReply* response)
{
    if (!request) return ::grpc::Status(::grpc::StatusCode::INVALID_ARGUMENT, "no request");
    LOCK(cs_main);
    CBlockIndex* pindex = chainActive[request->height()];
    if (!pindex) return ::grpc::Status(::grpc::StatusCode::NOT_FOUND, "height");
    response->set_hash(pindex->GetBlockHash().GetHex());
    response->set_height(pindex->nHeight);
    return ::grpc::Status::OK;
}

::grpc::Status NodeServiceImpl::BroadcastTransaction(::grpc::ServerContext*, const theminerzcoin::RawTransaction* request,
                                                    theminerzcoin::BroadcastReply* response)
{
    if (!request) return ::grpc::Status(::grpc::StatusCode::INVALID_ARGUMENT, "no request");
    std::string err;
    uint256 txid;
    if (!DecodeHexTx(txid, request->hex())) {
        return ::grpc::Status(::grpc::StatusCode::INVALID_ARGUMENT, "decode error");
    }
    response->set_txid(txid.ToString());
    response->set_success(true);
    return ::grpc::Status::OK;
}

void StartNodeGrpcServer(const std::string& address)
{
    NodeServiceImpl service;
    grpc::ServerBuilder builder;
    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    g_server = builder.BuildAndStart();
}

void StopNodeGrpcServer()
{
    if (g_server) {
        g_server->Shutdown();
        g_server.reset();
    }
}
