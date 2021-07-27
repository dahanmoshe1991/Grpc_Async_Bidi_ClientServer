#pragma once
#include <string>
#include "Utils.h"
#include "RpcUtilCallbackInterface.h"
#include "BaseGRpcClient.h"
#include "RpcUtilCb.h"

class BaseGRpcWrapper
{
	public:
		// Connect to gRpc server (Default ip - LocalHost)
		bool Connect(const std::string& ipAdress, const std::string& port); 
		// Singelton pattern
		static BaseGRpcWrapper* GetInstance(RpcUtilCallbackInterface* cb);
		void SetCallback(RpcUtilCallbackInterface* cb);

		// Communication Messages
		bool SayHello(const std::string& user);
		void SayHelloAsync(const std::string& user);
		void StartBidiStream();

	private:
		BaseGRpcWrapper();
		BaseGRpcWrapper(RpcUtilCallbackInterface* cb);
		~BaseGRpcWrapper();

		// Members
		static BaseGRpcWrapper* m_instance;
		RpcUtilCallbackInterface* m_cb;
		BaseGRpcClient* m_pClient;
};

