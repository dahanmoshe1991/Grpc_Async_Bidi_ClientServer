// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: BaseGRpcServer.proto

#include "BaseGRpcServer.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
namespace BaseGRpc {
}  // namespace BaseGRpc
static constexpr ::PROTOBUF_NAMESPACE_ID::Metadata* file_level_metadata_BaseGRpcServer_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_BaseGRpcServer_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_BaseGRpcServer_2eproto = nullptr;
const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_BaseGRpcServer_2eproto::offsets[1] = {};
static constexpr ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema* schemas = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::Message* const* file_default_instances = nullptr;

const char descriptor_table_protodef_BaseGRpcServer_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\024BaseGRpcServer.proto\022\010BaseGRpc\032\026BaseGR"
  "pcMessages.proto2\303\002\n\016BaseGRpcServer\0229\n\tH"
  "andshake\022\025.BaseGRpc.VoidMessage\032\025.BaseGR"
  "pc.VoidMessage\0228\n\010SayHello\022\026.BaseGRpc.He"
  "lloRequest\032\024.BaseGRpc.HelloReply\022=\n\014clie"
  "ntStream\022\024.BaseGRpc.IntMessage\032\025.BaseGRp"
  "c.BoolMessage(\001\022>\n\014serverStream\022\025.BaseGR"
  "pc.BoolMessage\032\025.BaseGRpc.BoolMessage0\001\022"
  "=\n\nBidiStream\022\024.BaseGRpc.IntMessage\032\025.Ba"
  "seGRpc.BoolMessage(\0010\001b\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_BaseGRpcServer_2eproto_deps[1] = {
  &::descriptor_table_BaseGRpcMessages_2eproto,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_BaseGRpcServer_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_BaseGRpcServer_2eproto = {
  false, false, 390, descriptor_table_protodef_BaseGRpcServer_2eproto, "BaseGRpcServer.proto", 
  &descriptor_table_BaseGRpcServer_2eproto_once, descriptor_table_BaseGRpcServer_2eproto_deps, 1, 0,
  schemas, file_default_instances, TableStruct_BaseGRpcServer_2eproto::offsets,
  file_level_metadata_BaseGRpcServer_2eproto, file_level_enum_descriptors_BaseGRpcServer_2eproto, file_level_service_descriptors_BaseGRpcServer_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK ::PROTOBUF_NAMESPACE_ID::Metadata
descriptor_table_BaseGRpcServer_2eproto_metadata_getter(int index) {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_BaseGRpcServer_2eproto);
  return descriptor_table_BaseGRpcServer_2eproto.file_level_metadata[index];
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_BaseGRpcServer_2eproto(&descriptor_table_BaseGRpcServer_2eproto);
namespace BaseGRpc {

// @@protoc_insertion_point(namespace_scope)
}  // namespace BaseGRpc
PROTOBUF_NAMESPACE_OPEN
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
