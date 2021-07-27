#include "BaseGRpcClient.h"
#include "BaseGrpcChannel.h"
#include <iostream>
#include <grpcpp/grpcpp.h>
#include "MessageToClass.h"
#include "ClassToMessage.h"
#include "Utils.h"
#include <thread>
#include <memory>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

BaseGRpcClient::BaseGRpcClient(RpcUtilCallbackInterface* cb) : m_cb(cb), startStreaming_(false), m_BaseGrpcConnected(false),
streamContext_(new ClientContext), m_BaseGrpcChannel(new BaseGrpcChannel())
{
}

BaseGRpcClient::~BaseGRpcClient()
{
	cq_.Shutdown();
	delete m_BaseGrpcChannel;
	delete m_cb;
}

// Create our channel
bool BaseGRpcClient::CreateChannel(const std::string& ipAdress, const std::string& port)
{
	// We use our channel class to hide implementation for other projects
	bool isConnected = m_BaseGrpcChannel->CreateChannel(ipAdress, port);
	if (isConnected && !asyncUnaryThread_.joinable())
		asyncUnaryThread_ = std::thread(&BaseGRpcClient::AsyncCompleteRpc, this);
	return isConnected;
}

// We use this to try calling the server until we get a response
bool BaseGRpcClient::CheckConnection() {
	m_BaseGrpcConnected = Handshake();
	return m_BaseGrpcConnected;
}

// Sets connection to false
void BaseGRpcClient::BaseGrpcDisconnected() {
	m_BaseGrpcConnected = false;
}

void BaseGRpcClient::StartBidiStream(BaseGRpcClient* client) {
	cout << "streamThread_ join" << std::endl;
	if (streamThread_.joinable())
		streamThread_.join();
	streamThread_ = std::thread(&BaseGRpcClient::BidiStream, this, m_BaseGrpcChannel->GetStub());
}

//************************************ "Connectivity" services ************************************
bool BaseGRpcClient::Handshake() {
	// Each request must have its own context
	ClientContext context;
	// This will hold our request message
	BaseGRpc::VoidMessage request;
	// This wil hold the response message 
	BaseGRpc::VoidMessage reply;
	// Call the function
	Status status = (m_BaseGrpcChannel->GetStub())->Handshake(&context, request, &reply);
	// We return the status to check the connecteion
	if (status.error_code() != grpc::OK) {
		cout << "Failed on Handshake message. error_message: " << status.error_message() << endl;
		return false;
	}
	return true;
}

//************************************ Messages ************************************

bool BaseGRpcClient::SayHello(const std::string& user) {
	// Data we are sending to the server.
	BaseGRpc::HelloRequest request;
	request.set_name(user);
	// Each request must have its own context
	ClientContext context;
	// This wil hold the response message 
	BaseGRpc::HelloReply reply;
	// Call the function
	Status status = (m_BaseGrpcChannel->GetStub())->SayHello(&context, request, &reply);
	// We return the status to check the connecteion
	if (status.error_code() != grpc::OK) {
		cout << "Failed on SayHello message. error_message: "<< status.error_message() << endl;
		return false;
	}
	cout << reply.message() << endl;
	return true;
}

//************************************ Async Messages & handeling ************************************
	// Assembles the client's payload and sends it to the server.
void BaseGRpcClient::SayHelloAsync(const std::string& user) {
	// Data we are sending to the server.
	BaseGRpc::HelloRequest request;
	request.set_name(user);

	// Call object to store rpc data
	Utils::AsyncClientCall<BaseGRpc::HelloReply>* call = new Utils::AsyncClientCall<BaseGRpc::HelloReply>;
	call->replyType = ClassToMessage::GetAsyncMessageTag(Utils::AsyncMessageTag::SayHello);

	// stub_->PrepareAsyncSayHello() creates an RPC object, returning
	// an instance to store in "call" but does not actually start the RPC
	// Because we are using the asynchronous API, we need to hold on to
	// the "call" instance in order to get updates on the ongoing RPC.
	call->response_reader =
		(m_BaseGrpcChannel->GetStub())->PrepareAsyncSayHello(&call->context, request, &cq_);

	// StartCall initiates the RPC call
	call->response_reader->StartCall();

	// Request that, upon completion of the RPC, "reply" be updated with the
	// server's response; "status" with the indication of whether the operation
	// was successful. Tag the request with the memory address of the call object.
	call->response_reader->Finish(&call->reply, &call->status, (void*)call);
}


void BaseGRpcClient::BidiStream(std::shared_ptr<BaseGRpc::BaseGRpcServer::Stub> stub) {
	streamContext_ = new ClientContext();
	BaseGRpc::BoolMessage boolMessage;
	try
	{
		std::shared_ptr<grpc::ClientReaderWriter<BaseGRpc::IntMessage, BaseGRpc::BoolMessage> > stream(
			stub->BidiStream(streamContext_));

		stream->Write(ClassToMessage::BuildIntMessage(m_cb->DoSomthing_Three()));
		while (m_continueStream && stream->Read(&boolMessage)) {
			std::cout << "Got boolMessage " << std::endl;
			if (m_continueStream) {
				std::cout << "sending new IntMessage " << std::endl;
				stream->Write(ClassToMessage::BuildIntMessage(m_cb->DoSomthing_Three()));
			}
		}
		std::cout << "closing stream" << std::endl;

		stream->WritesDone();
		Status status = stream->Finish();
		std::cout << "**finished stream" << std::endl;
		if (!status.ok()) {
			std::cout << "slicesStream rpc status: " << status.error_message() << std::endl;
		}

	}
	catch (const std::exception& ex)
	{
		std::cout << "slicesStream rpc failed, error: " << ex.what() << endl;
	}

	delete streamContext_;
}

// Loop while listening for completed responses.
void BaseGRpcClient::AsyncCompleteRpc() {
	void* got_tag;
	bool ok = false;

	// Block until the next result is available in the completion queue "cq".
	while (cq_.Next(&got_tag, &ok)) {
		try
		{
			if (ok)
				HandleAsyncMessage(ok, got_tag);
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << std::endl;
		}
	}
}

//the tag contains refrence for the sent call & needed to be casted appropriatly then handle & delete
void BaseGRpcClient::HandleAsyncMessage(bool ok, void* tag) {
	//replyType contains the type of message so we can cast for the specific reply
	Utils::AsyncClientCall<BaseGRpc::VoidMessage>* baseCall = static_cast<Utils::AsyncClientCall<BaseGRpc::VoidMessage>*>(tag);

	switch (Utils::s_mapMessagesTag[baseCall->replyType])
	{
	case Utils::AsyncMessageTag::SayHello: {
		Utils::AsyncClientCall<BaseGRpc::HelloReply>* helloCall = static_cast<Utils::AsyncClientCall<BaseGRpc::HelloReply>*>(tag);
		GPR_ASSERT(ok);
		if (helloCall->status.ok())
			cout << "**Hello received: " << helloCall->reply.message() << std::endl;
		else
			std::cout << "RPC failed" << std::endl;

		// Once we're complete, deallocate the call object.
		delete helloCall;
	}
	break;
	
	/* 
		Add here more handling cases for async messages 
	*/

	default:
		std::cout << "received false string tag -  RPC failed" << std::endl;
		break;
	}
}