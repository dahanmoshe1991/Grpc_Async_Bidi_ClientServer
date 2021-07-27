#include "BaseGrpcChannel.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

#define KEEP_ALIVE_TIME_MS 60000 // 1 min
#define MAX_MSG_SIZE 64 * 1024 * 1024 // 64 MB

// Create our channel
bool BaseGrpcChannel::CreateChannel(const std::string& ipAdress, const std::string& port)
{
	// target string format is ip:port
	std::string target_str = ipAdress + ":" + port;

	// Channel arguments (client side)
	grpc::ChannelArguments channelArguments;

	// Set keep alive on client side for KEEP_ALIVE_TIME_MS 
	channelArguments.SetInt(GRPC_ARG_KEEPALIVE_TIME_MS, KEEP_ALIVE_TIME_MS);
	channelArguments.SetInt(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, 1);
	channelArguments.SetMaxReceiveMessageSize(MAX_MSG_SIZE);

	// We first generate our (custom) channel
	m_Channel = grpc::CreateCustomChannel(target_str, grpc::InsecureChannelCredentials(), channelArguments);
	// we then generate our stub
	m_Stub = BaseGRpc::BaseGRpcServer::NewStub(m_Channel);

	// We try to get the channel state
	grpc_connectivity_state curState = m_Channel->GetState(true);

	// If we are ready after initial connection, everything connected succesfuly.
	if (curState == GRPC_CHANNEL_IDLE) return true;

	// Anything else means something went wrong
	return false;
}

// Get the stub
std::shared_ptr<BaseGRpc::BaseGRpcServer::Stub> BaseGrpcChannel::GetStub() {
	return m_Stub;
}