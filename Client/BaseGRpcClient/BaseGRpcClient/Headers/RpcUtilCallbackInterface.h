#pragma once
#include "Utils.h"

class RpcUtilCallbackInterface
{
	public:
		virtual bool	DoSomthing_One() = 0;
		virtual void	DoSomthing_Two(bool input) = 0;
		virtual int		DoSomthing_Three() = 0;
};