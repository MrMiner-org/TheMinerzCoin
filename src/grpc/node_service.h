#pragma once
#include "node.grpc.pb.h"

class NodeServiceImpl final : public theminerzcoin::Node::Service {
public:
    ::grpc::Status GetBlock(::grpc::ServerContext* context, const theminerzcoin::BlockRequest* request,
                            theminerzcoin::BlockReply* response) override;
    ::grpc::Status BroadcastTransaction(::grpc::ServerContext* context, const theminerzcoin::RawTransaction* request,
                                       theminerzcoin::BroadcastReply* response) override;
};

void StartNodeGrpcServer(const std::string& address);
void StopNodeGrpcServer();
