#pragma once
#include <memory>
#include "grpcpp\grpcpp.h"
#include "Utils.h"

// Our generated header
#include "BaseGRpcMessages.pb.h"

using namespace std;
//Note: The way we pass data is not specified individualy, notice different output types 
// We define functions that convert messages to their respective class here
// Make sure you check if a vectors need to be cleared and populatd or built from scratch
// Use the utils defined at the start of this header (BuildVector , PopulateVector , PopulateArray , ConvertEnum )
namespace MessageToClass {

	template <typename enumType>
	// Simple int -> enum converter
	// This should be used when for usage in BuildVector/array for converting repeated int fields to enum
	enumType ConvertEnum(int integer) {
		return (enumType)integer;
	}

	// Adapt message to to response code
	Utils::ResponseCode BuildResponseCode(const BaseGRpc::ResponseCodeMessage& message) {
		return (Utils::ResponseCode)message.responsecode();
	}

	template <class type>
	// This functions takes any repeated field and converts it to a vector of <type>
	std::vector<type> BuildVector(const google::protobuf::RepeatedField<type>& repField) {
		return std::vector<type>(repField.begin(), repField.end());
	}

	template <class type>
	// This functions takes any repeated field and converts it to a vector of <type>
	std::vector<type> BuildVector(const google::protobuf::RepeatedPtrField<type>& repField) {
		return std::vector<type>(repField.begin(), repField.end());
	}

	// This function takes a repeated field message of type and creates a vector of structType building each object in the output vector using the messageConverter functions
	// Use this for custom types!
	template<class messageType, class structType>
	std::vector<structType> BuildVector(const google::protobuf::RepeatedPtrField<messageType>& repField, structType(*messageConverter)(const messageType& msg)) {
		//Create our vector
		vector<structType> structVector;
		// Start pushing our converted types
		for (auto msg : repField) {
			structVector.push_back(messageConverter(msg));
		}
		return structVector;
	}

	// This function takes a repeated ptr field message of type and populates an exisiting vector of type 
	// Use this for custom types!
	template<class type>
	void PopulateVector(const google::protobuf::RepeatedPtrField<type>& repField, vector<type>& structVector) {
		//structVector.clear(); // NOTE: This seems to not be used (We only add data without clearing the vector)
		// Start pushing our converted types
		for (auto msg : repField) {
			structVector.push_back(msg);
		}
	}

	// This function takes a repeated field message of type and populates an exisiting vector of type 
	// Use this for custom types!
	template<class type>
	void PopulateVector(const google::protobuf::RepeatedField<type>& repField, vector<type>& structVector) {
		//structVector.clear(); // NOTE: This seems to not be used (We only add data without clearing the vector)
		// Start pushing our converted types
		for (auto msg : repField) {
			structVector.push_back(msg);
		}
	}

	// This function takes a repeated field message of type and populates an exisiting vector of structType building each object in the output vector using the messageConverter functions
	// Use this for custom types!
	template<class messageType, class structType>
	void PopulateVector(const google::protobuf::RepeatedPtrField<messageType>& repField, vector<structType>& structVector, structType(*messageConverter)(const messageType& msg)) {
		//structVector.clear(); // NOTE: This seems to not be used (We only add data without clearing the vector)
		// Start pushing our converted types
		for (auto msg : repField) {
			structVector.push_back(messageConverter(msg));
		}
	}

	// This function takes a repeated field message of type and populates an exisiting vector of structType building each object in the output vector using the messageConverter functions
	// Use this for custom types!
	template<class messageType, class structType>
	void PopulateVector(const google::protobuf::RepeatedField<messageType>& repField, vector<structType>& structVector, structType(*messageConverter)(messageType msg)) {
		//structVector.clear(); // NOTE: This seems to not be used (We only add data without clearing the vector)
		// Start pushing our converted types
		for (auto msg : repField) {
			structVector.push_back(messageConverter(msg));
		}
	}

	// This function takes a repeated field message of type and populates an exisiting vector of structType building each object in the output vector using the messageConverter functions
	// This version is used for populating vectors of based types
	// Use this for custom types!
	template<class messageType, class baseType, class structType>
	void PopulateVector(const google::protobuf::RepeatedPtrField<messageType>& repField, vector<baseType>& structVector, structType(*messageConverter)(const messageType& msg)) {
		//structVector.clear(); // NOTE: This seems to not be used (We only add data without clearing the vector)
		// Start pushing our converted types
		for (auto msg : repField) {
			structVector.push_back(messageConverter(msg));
		}
	}

	// This function takes a repeated field message of type and populates an exisiting array of structType building each object in the output vector using the messageConverter functions
	// Use this for custom types!
	template<class messageType, class structType>
	void PopulateArray(const google::protobuf::RepeatedPtrField<messageType>& repField, structType arr[], size_t size, structType(*messageConverter)(const messageType& msg)) {
		// Start pushing our converted types
		for (int i = 0; i < size; i++) {
			arr[i] = messageConverter(repField.at(i));
		}
	}

	// This function takes a repeated field message of type and populates an exisiting array of structType building each object in the output vector using the messageConverter functions
	// This version is mostly for enums
	template<class messageType, class structType>
	void PopulateArray(const google::protobuf::RepeatedField<messageType>& repField, structType arr[], size_t size, structType(*messageConverter)(messageType msg)) {
		// Start pushing our converted types
		for (int i = 0; i < size; i++) {
			arr[i] = messageConverter(repField.at(i));
		}
	}
}