#include "pch.h"
#include "BaseGRpcWrpperTestCase.h"

/// <summary>
/// BaseGRpcClient tests
/// Prerequists:
/// make sure Cyclone is Running (BaseGRpcServer)
/// </summary>

TEST_F(BaseGRpcWrpperTestCase, Connection) {
	// act
	bool connected = ut_wrapper->Connect("127.0.0.1", "5002");
	// assert
	EXPECT_TRUE(connected);
}

TEST_F(BaseGRpcWrpperTestCase, SayHello) {
	// Arrange
	bool connected = ut_wrapper->Connect("127.0.0.1", "5002");
	EXPECT_TRUE(connected);

	// act
	bool ans = ut_wrapper->SayHello("User-Name");

	// assert
	EXPECT_TRUE(ans);
}


/// <summary>
/// initializes the framework and must be called before RUN_ALL_TESTS. 
/// RUN_ALL_TESTS must be called only once in the code because multiple calls to it 
/// conflict with some of the advanced features of the framework and, therefore, are not supported.
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}