// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Protbload.proto

#include "Protbload.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// This is a temporary google only hack
#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
#include "third_party/protobuf/version.h"
#endif
// @@protoc_insertion_point(includes)

namespace Protbload {
class ADDDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<ADD>
      _instance;
} _ADD_default_instance_;
class RESULTDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<RESULT>
      _instance;
} _RESULT_default_instance_;
}  // namespace Protbload
namespace protobuf_Protbload_2eproto {
static void InitDefaultsADD() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::Protbload::_ADD_default_instance_;
    new (ptr) ::Protbload::ADD();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::Protbload::ADD::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_ADD =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsADD}, {}};

static void InitDefaultsRESULT() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::Protbload::_RESULT_default_instance_;
    new (ptr) ::Protbload::RESULT();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::Protbload::RESULT::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_RESULT =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsRESULT}, {}};

void InitDefaults() {
  ::google::protobuf::internal::InitSCC(&scc_info_ADD.base);
  ::google::protobuf::internal::InitSCC(&scc_info_RESULT.base);
}

::google::protobuf::Metadata file_level_metadata[2];

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::Protbload::ADD, _has_bits_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::Protbload::ADD, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::Protbload::ADD, agv1_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::Protbload::ADD, agv2_),
  0,
  1,
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::Protbload::RESULT, _has_bits_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::Protbload::RESULT, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::Protbload::RESULT, answer_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::Protbload::RESULT, exflag_),
  0,
  1,
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 7, sizeof(::Protbload::ADD)},
  { 9, 16, sizeof(::Protbload::RESULT)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::Protbload::_ADD_default_instance_),
  reinterpret_cast<const ::google::protobuf::Message*>(&::Protbload::_RESULT_default_instance_),
};

void protobuf_AssignDescriptors() {
  AddDescriptors();
  AssignDescriptors(
      "Protbload.proto", schemas, file_default_instances, TableStruct::offsets,
      file_level_metadata, NULL, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static ::google::protobuf::internal::once_flag once;
  ::google::protobuf::internal::call_once(once, protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_PROTOBUF_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 2);
}

void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n\017Protbload.proto\022\tProtbload\"!\n\003ADD\022\014\n\004a"
      "gv1\030\001 \002(\005\022\014\n\004agv2\030\002 \002(\005\"/\n\006RESULT\022\016\n\006ans"
      "wer\030\001 \002(\005\022\025\n\006exflag\030\002 \001(\010:\005false"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 112);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "Protbload.proto", &protobuf_RegisterTypes);
}

void AddDescriptors() {
  static ::google::protobuf::internal::once_flag once;
  ::google::protobuf::internal::call_once(once, AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at dynamic initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;
}  // namespace protobuf_Protbload_2eproto
namespace Protbload {

// ===================================================================

void ADD::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int ADD::kAgv1FieldNumber;
const int ADD::kAgv2FieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

ADD::ADD()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  ::google::protobuf::internal::InitSCC(
      &protobuf_Protbload_2eproto::scc_info_ADD.base);
  SharedCtor();
  // @@protoc_insertion_point(constructor:Protbload.ADD)
}
ADD::ADD(const ADD& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&agv1_, &from.agv1_,
    static_cast<size_t>(reinterpret_cast<char*>(&agv2_) -
    reinterpret_cast<char*>(&agv1_)) + sizeof(agv2_));
  // @@protoc_insertion_point(copy_constructor:Protbload.ADD)
}

void ADD::SharedCtor() {
  ::memset(&agv1_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&agv2_) -
      reinterpret_cast<char*>(&agv1_)) + sizeof(agv2_));
}

ADD::~ADD() {
  // @@protoc_insertion_point(destructor:Protbload.ADD)
  SharedDtor();
}

void ADD::SharedDtor() {
}

void ADD::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ::google::protobuf::Descriptor* ADD::descriptor() {
  ::protobuf_Protbload_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_Protbload_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const ADD& ADD::default_instance() {
  ::google::protobuf::internal::InitSCC(&protobuf_Protbload_2eproto::scc_info_ADD.base);
  return *internal_default_instance();
}


void ADD::Clear() {
// @@protoc_insertion_point(message_clear_start:Protbload.ADD)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 3u) {
    ::memset(&agv1_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&agv2_) -
        reinterpret_cast<char*>(&agv1_)) + sizeof(agv2_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

bool ADD::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Protbload.ADD)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 agv1 = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {
          set_has_agv1();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &agv1_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // required int32 agv2 = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(16u /* 16 & 0xFF */)) {
          set_has_agv2();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &agv2_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:Protbload.ADD)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Protbload.ADD)
  return false;
#undef DO_
}

void ADD::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Protbload.ADD)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required int32 agv1 = 1;
  if (cached_has_bits & 0x00000001u) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->agv1(), output);
  }

  // required int32 agv2 = 2;
  if (cached_has_bits & 0x00000002u) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->agv2(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Protbload.ADD)
}

::google::protobuf::uint8* ADD::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:Protbload.ADD)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required int32 agv1 = 1;
  if (cached_has_bits & 0x00000001u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->agv1(), target);
  }

  // required int32 agv2 = 2;
  if (cached_has_bits & 0x00000002u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->agv2(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Protbload.ADD)
  return target;
}

size_t ADD::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:Protbload.ADD)
  size_t total_size = 0;

  if (has_agv1()) {
    // required int32 agv1 = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->agv1());
  }

  if (has_agv2()) {
    // required int32 agv2 = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->agv2());
  }

  return total_size;
}
size_t ADD::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Protbload.ADD)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  if (((_has_bits_[0] & 0x00000003) ^ 0x00000003) == 0) {  // All required fields are present.
    // required int32 agv1 = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->agv1());

    // required int32 agv2 = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->agv2());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void ADD::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Protbload.ADD)
  GOOGLE_DCHECK_NE(&from, this);
  const ADD* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const ADD>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Protbload.ADD)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Protbload.ADD)
    MergeFrom(*source);
  }
}

void ADD::MergeFrom(const ADD& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Protbload.ADD)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 3u) {
    if (cached_has_bits & 0x00000001u) {
      agv1_ = from.agv1_;
    }
    if (cached_has_bits & 0x00000002u) {
      agv2_ = from.agv2_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void ADD::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Protbload.ADD)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ADD::CopyFrom(const ADD& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Protbload.ADD)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ADD::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;
  return true;
}

void ADD::Swap(ADD* other) {
  if (other == this) return;
  InternalSwap(other);
}
void ADD::InternalSwap(ADD* other) {
  using std::swap;
  swap(agv1_, other->agv1_);
  swap(agv2_, other->agv2_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
}

::google::protobuf::Metadata ADD::GetMetadata() const {
  protobuf_Protbload_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_Protbload_2eproto::file_level_metadata[kIndexInFileMessages];
}


// ===================================================================

void RESULT::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int RESULT::kAnswerFieldNumber;
const int RESULT::kExflagFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

RESULT::RESULT()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  ::google::protobuf::internal::InitSCC(
      &protobuf_Protbload_2eproto::scc_info_RESULT.base);
  SharedCtor();
  // @@protoc_insertion_point(constructor:Protbload.RESULT)
}
RESULT::RESULT(const RESULT& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&answer_, &from.answer_,
    static_cast<size_t>(reinterpret_cast<char*>(&exflag_) -
    reinterpret_cast<char*>(&answer_)) + sizeof(exflag_));
  // @@protoc_insertion_point(copy_constructor:Protbload.RESULT)
}

void RESULT::SharedCtor() {
  ::memset(&answer_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&exflag_) -
      reinterpret_cast<char*>(&answer_)) + sizeof(exflag_));
}

RESULT::~RESULT() {
  // @@protoc_insertion_point(destructor:Protbload.RESULT)
  SharedDtor();
}

void RESULT::SharedDtor() {
}

void RESULT::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ::google::protobuf::Descriptor* RESULT::descriptor() {
  ::protobuf_Protbload_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_Protbload_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const RESULT& RESULT::default_instance() {
  ::google::protobuf::internal::InitSCC(&protobuf_Protbload_2eproto::scc_info_RESULT.base);
  return *internal_default_instance();
}


void RESULT::Clear() {
// @@protoc_insertion_point(message_clear_start:Protbload.RESULT)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 3u) {
    ::memset(&answer_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&exflag_) -
        reinterpret_cast<char*>(&answer_)) + sizeof(exflag_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

bool RESULT::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Protbload.RESULT)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 answer = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {
          set_has_answer();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &answer_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional bool exflag = 2 [default = false];
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(16u /* 16 & 0xFF */)) {
          set_has_exflag();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &exflag_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:Protbload.RESULT)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Protbload.RESULT)
  return false;
#undef DO_
}

void RESULT::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Protbload.RESULT)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required int32 answer = 1;
  if (cached_has_bits & 0x00000001u) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->answer(), output);
  }

  // optional bool exflag = 2 [default = false];
  if (cached_has_bits & 0x00000002u) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(2, this->exflag(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Protbload.RESULT)
}

::google::protobuf::uint8* RESULT::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:Protbload.RESULT)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required int32 answer = 1;
  if (cached_has_bits & 0x00000001u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->answer(), target);
  }

  // optional bool exflag = 2 [default = false];
  if (cached_has_bits & 0x00000002u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(2, this->exflag(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Protbload.RESULT)
  return target;
}

size_t RESULT::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Protbload.RESULT)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  // required int32 answer = 1;
  if (has_answer()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->answer());
  }
  // optional bool exflag = 2 [default = false];
  if (has_exflag()) {
    total_size += 1 + 1;
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void RESULT::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Protbload.RESULT)
  GOOGLE_DCHECK_NE(&from, this);
  const RESULT* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const RESULT>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Protbload.RESULT)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Protbload.RESULT)
    MergeFrom(*source);
  }
}

void RESULT::MergeFrom(const RESULT& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Protbload.RESULT)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 3u) {
    if (cached_has_bits & 0x00000001u) {
      answer_ = from.answer_;
    }
    if (cached_has_bits & 0x00000002u) {
      exflag_ = from.exflag_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void RESULT::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Protbload.RESULT)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void RESULT::CopyFrom(const RESULT& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Protbload.RESULT)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool RESULT::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;
  return true;
}

void RESULT::Swap(RESULT* other) {
  if (other == this) return;
  InternalSwap(other);
}
void RESULT::InternalSwap(RESULT* other) {
  using std::swap;
  swap(answer_, other->answer_);
  swap(exflag_, other->exflag_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
}

::google::protobuf::Metadata RESULT::GetMetadata() const {
  protobuf_Protbload_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_Protbload_2eproto::file_level_metadata[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace Protbload
namespace google {
namespace protobuf {
template<> GOOGLE_PROTOBUF_ATTRIBUTE_NOINLINE ::Protbload::ADD* Arena::CreateMaybeMessage< ::Protbload::ADD >(Arena* arena) {
  return Arena::CreateInternal< ::Protbload::ADD >(arena);
}
template<> GOOGLE_PROTOBUF_ATTRIBUTE_NOINLINE ::Protbload::RESULT* Arena::CreateMaybeMessage< ::Protbload::RESULT >(Arena* arena) {
  return Arena::CreateInternal< ::Protbload::RESULT >(arena);
}
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)
