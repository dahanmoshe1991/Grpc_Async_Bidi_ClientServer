#pragma once
#include <grpcpp/grpcpp.h>
#include "BaseGRpcServer.grpc.pb.h"
#include "BaseGRpcMessages.grpc.pb.h"
#include "BaseGRpcMessages.pb.h"
#include "BaseGRpcServer.pb.h"

class BaseGrpcChannel
{
public:
	// Create channel and check connection
	bool CreateChannel(const std::string& ipAdress, const std::string& port);
	// Get the stub
	std::shared_ptr<BaseGRpc::BaseGRpcServer::Stub> GetStub();

private:
	// our channel
	std::shared_ptr<grpc::Channel>  m_Channel;
	// our stub
	std::shared_ptr<BaseGRpc::BaseGRpcServer::Stub> m_Stub;
};

