#pragma once
#include "pch.h"
#include <grpc/grpc.h>
#include "../BaseGRpcClient/Headers/BaseGRpcWrapper.h"
#include "../BaseGRpcClient/Headers/RpcUtilCb.h"

class BaseGRpcWrpperTestCase : public ::testing::Test {
protected:
    void SetUp() override {
        ut_wrapper = BaseGRpcWrapper::GetInstance(new RpcUtilCb());
    }

    void TearDown() override { 
        ut_wrapper = nullptr; 
    }

    BaseGRpcWrapper* ut_wrapper = nullptr;

    BaseGRpcWrpperTestCase() {}
};
