#pragma once
#include <string>
#include <vector>
#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>
#include <map>

#pragma once
namespace Utils
{
	// *********** Utility/Base ********************


	// ******************** Enum  ********************
	enum class ResponseCode
	{
		Success = 0,
		NotValid = -1,
		Error = -2,
		InvalidInput = -3
	};

	// Add here other unary async messages tags
	enum class AsyncMessageTag {
		SayHello
	};


	// Map to associate the strings with the enum values
	static std::map<std::string, Utils::AsyncMessageTag> s_mapMessagesTag{
		{"SayHello",AsyncMessageTag::SayHello},
	};

	// ******************** Communication Structs ********************

	// struct for keeping state and data information
	template <typename P>
	class AsyncClientCall {
	public:
		std::string replyType;
		// Container for the data we expect from the server.
		P reply;

		// Context for the client. It could be used to convey extra information to
		// the server and/or tweak certain RPC behaviors.
		grpc::ClientContext context;

		// Storage for the status of the RPC upon completion.
		grpc::Status status;

		std::unique_ptr<grpc::ClientAsyncResponseReader<P>> response_reader;
	};

	template <typename W, typename R>
	class AsyncBidiClientCall {
	public:
		std::string replyType;
		// Container for the data we expect from the server.
		W request;
		R reply;

		// Context for the client. It could be used to convey extra information to
		// the server and/or tweak certain RPC behaviors.
		grpc::ClientContext context;

		// Storage for the status of the RPC upon completion.
		grpc::Status status;

		std::unique_ptr<grpc::ClientAsyncReaderWriter<W, R>> reader_writer;
	};

}
