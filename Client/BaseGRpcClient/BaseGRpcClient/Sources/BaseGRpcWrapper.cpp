#include "BaseGRpcWrapper.h"


BaseGRpcWrapper* BaseGRpcWrapper::m_instance = 0;

BaseGRpcWrapper::BaseGRpcWrapper(RpcUtilCallbackInterface* cb) : m_cb(cb)
{
	m_pClient = new BaseGRpcClient(cb);
}

BaseGRpcWrapper::BaseGRpcWrapper() : m_cb(new RpcUtilCb()), m_pClient(new BaseGRpcClient(m_cb))
{
}

BaseGRpcWrapper::~BaseGRpcWrapper()
{
	delete m_pClient;
}

bool BaseGRpcWrapper::Connect(const std::string& ipAdress, const std::string& port)
{
	return  m_pClient->CreateChannel(ipAdress, port) && m_pClient->CheckConnection();
}

BaseGRpcWrapper* BaseGRpcWrapper::GetInstance(RpcUtilCallbackInterface* cb)
{
	if (!m_instance)
	{
		m_instance = new BaseGRpcWrapper(cb);
	}

	return m_instance;
}

void BaseGRpcWrapper::SetCallback(RpcUtilCallbackInterface* cb)
{
	m_cb = cb;
}

bool BaseGRpcWrapper::SayHello(const std::string& user) {
	return m_pClient->SayHello(user);
}

void BaseGRpcWrapper::SayHelloAsync(const std::string& user) {
	return m_pClient->SayHelloAsync(user);
}

void BaseGRpcWrapper::StartBidiStream() {
	m_pClient->StartBidiStream(m_pClient);
}