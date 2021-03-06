// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: BaseGRpcServer.proto

#include "BaseGRpcServer.pb.h"
#include "BaseGRpcServer.grpc.pb.h"

#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/sync_stream.h>
#include <gmock/gmock.h>
namespace BaseGRpc {

class MockBaseGRpcServerStub : public BaseGRpcServer::StubInterface {
 public:
  MOCK_METHOD3(Handshake, ::grpc::Status(::grpc::ClientContext* context, const ::BaseGRpc::VoidMessage& request, ::BaseGRpc::VoidMessage* response));
  MOCK_METHOD3(AsyncHandshakeRaw, ::grpc::ClientAsyncResponseReaderInterface< ::BaseGRpc::VoidMessage>*(::grpc::ClientContext* context, const ::BaseGRpc::VoidMessage& request, ::grpc::CompletionQueue* cq));
  MOCK_METHOD3(PrepareAsyncHandshakeRaw, ::grpc::ClientAsyncResponseReaderInterface< ::BaseGRpc::VoidMessage>*(::grpc::ClientContext* context, const ::BaseGRpc::VoidMessage& request, ::grpc::CompletionQueue* cq));
  MOCK_METHOD3(SayHello, ::grpc::Status(::grpc::ClientContext* context, const ::BaseGRpc::HelloRequest& request, ::BaseGRpc::HelloReply* response));
  MOCK_METHOD3(AsyncSayHelloRaw, ::grpc::ClientAsyncResponseReaderInterface< ::BaseGRpc::HelloReply>*(::grpc::ClientContext* context, const ::BaseGRpc::HelloRequest& request, ::grpc::CompletionQueue* cq));
  MOCK_METHOD3(PrepareAsyncSayHelloRaw, ::grpc::ClientAsyncResponseReaderInterface< ::BaseGRpc::HelloReply>*(::grpc::ClientContext* context, const ::BaseGRpc::HelloRequest& request, ::grpc::CompletionQueue* cq));
  MOCK_METHOD2(clientStreamRaw, ::grpc::ClientWriterInterface< ::BaseGRpc::IntMessage>*(::grpc::ClientContext* context, ::BaseGRpc::BoolMessage* response));
  MOCK_METHOD4(AsyncclientStreamRaw, ::grpc::ClientAsyncWriterInterface< ::BaseGRpc::IntMessage>*(::grpc::ClientContext* context, ::BaseGRpc::BoolMessage* response, ::grpc::CompletionQueue* cq, void* tag));
  MOCK_METHOD3(PrepareAsyncclientStreamRaw, ::grpc::ClientAsyncWriterInterface< ::BaseGRpc::IntMessage>*(::grpc::ClientContext* context, ::BaseGRpc::BoolMessage* response, ::grpc::CompletionQueue* cq));
  MOCK_METHOD2(serverStreamRaw, ::grpc::ClientReaderInterface< ::BaseGRpc::BoolMessage>*(::grpc::ClientContext* context, const ::BaseGRpc::BoolMessage& request));
  MOCK_METHOD4(AsyncserverStreamRaw, ::grpc::ClientAsyncReaderInterface< ::BaseGRpc::BoolMessage>*(::grpc::ClientContext* context, const ::BaseGRpc::BoolMessage& request, ::grpc::CompletionQueue* cq, void* tag));
  MOCK_METHOD3(PrepareAsyncserverStreamRaw, ::grpc::ClientAsyncReaderInterface< ::BaseGRpc::BoolMessage>*(::grpc::ClientContext* context, const ::BaseGRpc::BoolMessage& request, ::grpc::CompletionQueue* cq));
  MOCK_METHOD1(BidiStreamRaw, ::grpc::ClientReaderWriterInterface< ::BaseGRpc::IntMessage, ::BaseGRpc::BoolMessage>*(::grpc::ClientContext* context));
  MOCK_METHOD3(AsyncBidiStreamRaw, ::grpc::ClientAsyncReaderWriterInterface<::BaseGRpc::IntMessage, ::BaseGRpc::BoolMessage>*(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag));
  MOCK_METHOD2(PrepareAsyncBidiStreamRaw, ::grpc::ClientAsyncReaderWriterInterface<::BaseGRpc::IntMessage, ::BaseGRpc::BoolMessage>*(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq));
};

} // namespace BaseGRpc

