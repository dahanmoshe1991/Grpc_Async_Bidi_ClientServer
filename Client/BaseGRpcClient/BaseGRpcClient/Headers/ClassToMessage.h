#pragma once
#include <memory>
#include <iostream>
#include "grpcpp\grpcpp.h"
#include "Utils.h"
#include <string>
// Our generated header
#include "BaseGRpcMessages.grpc.pb.h"

// We define functions that convert classes to their respective message here
namespace ClassToMessage {

	// This functions takes a repeated field of messageType , an equivilant vector of struct type and a conversion function
	// It populates the repeated field with corresponding messageType messages by using messageConverter
	// Note: you needs to send the mutable_ version of field
	template<class messageType, class structType>
	void PopulateRepeatedField(::google::protobuf::RepeatedField<messageType>* msg, const std::vector<structType>& vec, messageType(*messageConverter)(const structType& data)) {
		for (auto data : vec) msg->Add(messageConverter(data));
	}

	// This functions takes a repeated field of Type and equivilant vector 
	// It populates the repeated field
	// Note: you needs to send the mutable_ version of field
	template<class Type>
	void PopulateRepeatedField(google::protobuf::RepeatedField<Type>* msg, const std::vector<Type>& vec) {
		for (auto data : vec) msg->Add(data);
	}

	// This functions takes a repeated field of type , an equivilant array of type and it's size
	// It populates the repeated field with corresponding messageType
	// This version is for primitives
	// Note: you needs to send the mutable_ version of field
	template<class type>
	void PopulateRepeatedField(google::protobuf::RepeatedField<type>* msg, type arr[], size_t size) {
		for (int i = 0; i < size; i++)
			msg->Add(arr[i]);
	}

	BaseGRpc::StringMessage  BuildStringMessage(std::string s) {
		BaseGRpc::StringMessage sMsg;
		sMsg.set_message(s);
		return sMsg;
	}

	BaseGRpc::IntMessage  BuildIntMessage(int i) {
		BaseGRpc::IntMessage iMsg;
		iMsg.set_message(i);
		return iMsg;
	}

	BaseGRpc::BoolMessage  BuildBoolMessage(bool b) {
		BaseGRpc::BoolMessage bMsg;
		bMsg.set_message(b);
		return bMsg;
	}

	std::string GetAsyncMessageTag(Utils::AsyncMessageTag mTag) {
		std::string tag;

		switch (mTag)
		{
		case Utils::AsyncMessageTag::SayHello:
			tag = "SayHello";
			break;

			//add here more Tag cases

		default:
			tag = "";
			break;
		}

		return tag;
	}
}