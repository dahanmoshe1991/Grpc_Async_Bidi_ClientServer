#pragma once
#include "RpcUtilCallbackInterface.h"

class RpcUtilCb :public RpcUtilCallbackInterface
{
public:

	RpcUtilCb() {};

	// Inherited via RpcUtilCallbackInterface
	virtual bool DoSomthing_One() override;

	virtual void DoSomthing_Two(bool input) override;

	virtual int DoSomthing_Three() override;

};

