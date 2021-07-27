#include "RpcUtilCb.h"
using namespace std;

bool RpcUtilCb::DoSomthing_One()
{
	cout << "DoSomthing_One" << endl;
	return true;
}

void RpcUtilCb::DoSomthing_Two(bool input)
{
	cout << "DoSomthing_Two, input: " << input << endl;
}

int RpcUtilCb::DoSomthing_Three()
{
	cout << "DoSomthing_Three" << endl;
	return 1;
}
