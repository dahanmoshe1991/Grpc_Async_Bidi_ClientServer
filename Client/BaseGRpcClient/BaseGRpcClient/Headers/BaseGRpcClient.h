#pragma once
#include <string>
#include <thread>
#include <vector> 
#include <grpcpp/impl/codegen/completion_queue.h>
#include "Utils.h"
#include "RpcUtilCallbackInterface.h"
#include "../Generated/BaseGRpcServer.grpc.pb.h"
// Forward Declarations
class BaseGrpcChannel; // This class is used in order to seperate other projects from dealing with grpc implementation

class BaseGRpcClient {

public:
	//************************************ Client functions ************************************
	BaseGRpcClient(RpcUtilCallbackInterface* cb);
	~BaseGRpcClient();

	// Create channel and check connection
	bool CreateChannel(const std::string& ipAdress, const std::string& port);

	// Check if connection succeeded
	bool CheckConnection();

	// Sets BaseGrpcConnected to false
	void BaseGrpcDisconnected();

	//************************************ Messages ************************************

	void StartBidiStream(BaseGRpcClient* client);
	bool SayHello(const std::string& user);
	void SayHelloAsync(const std::string& user);
	
	//Handling for Async operations
	//use this functions for Async Unary Messages
	void AsyncCompleteRpc();
	void HandleAsyncMessage(bool ok, void* tag);

	void BidiStream(std::shared_ptr<BaseGRpc::BaseGRpcServer::Stub> stub);
	// The producer-consumer queue we use to communicate asynchronously with the
	// gRPC runtime.
	grpc::CompletionQueue cq_;

	bool m_continueStream = false;
	std::thread asyncUnaryThread_;

	// Threads that notifies the gRPC completion queue tags.
	std::thread streamThread_;
	grpc::ClientContext* streamContext_;
	bool startStreaming_;

private:
	// Used for checking if connection occured
	bool Handshake();
	// flag to indicate if BaseGrpc is connected
	bool m_BaseGrpcConnected;
	// This handles eveything channel related
	BaseGrpcChannel* m_BaseGrpcChannel;

	RpcUtilCallbackInterface* m_cb;

	
};