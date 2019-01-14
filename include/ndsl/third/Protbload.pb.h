// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Protbload.proto

#ifndef PROTOBUF_INCLUDED_Protbload_2eproto
#define PROTOBUF_INCLUDED_Protbload_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3006000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_Protbload_2eproto 

namespace protobuf_Protbload_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[2];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_Protbload_2eproto
namespace Protbload {
class ADD;
class ADDDefaultTypeInternal;
extern ADDDefaultTypeInternal _ADD_default_instance_;
class RESULT;
class RESULTDefaultTypeInternal;
extern RESULTDefaultTypeInternal _RESULT_default_instance_;
}  // namespace Protbload
namespace google {
namespace protobuf {
template<> ::Protbload::ADD* Arena::CreateMaybeMessage<::Protbload::ADD>(Arena*);
template<> ::Protbload::RESULT* Arena::CreateMaybeMessage<::Protbload::RESULT>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace Protbload {

// ===================================================================

class ADD : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Protbload.ADD) */ {
 public:
  ADD();
  virtual ~ADD();

  ADD(const ADD& from);

  inline ADD& operator=(const ADD& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  ADD(ADD&& from) noexcept
    : ADD() {
    *this = ::std::move(from);
  }

  inline ADD& operator=(ADD&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ADD& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const ADD* internal_default_instance() {
    return reinterpret_cast<const ADD*>(
               &_ADD_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(ADD* other);
  friend void swap(ADD& a, ADD& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline ADD* New() const final {
    return CreateMaybeMessage<ADD>(NULL);
  }

  ADD* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<ADD>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const ADD& from);
  void MergeFrom(const ADD& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(ADD* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 agv1 = 1;
  bool has_agv1() const;
  void clear_agv1();
  static const int kAgv1FieldNumber = 1;
  ::google::protobuf::int32 agv1() const;
  void set_agv1(::google::protobuf::int32 value);

  // required int32 agv2 = 2;
  bool has_agv2() const;
  void clear_agv2();
  static const int kAgv2FieldNumber = 2;
  ::google::protobuf::int32 agv2() const;
  void set_agv2(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:Protbload.ADD)
 private:
  void set_has_agv1();
  void clear_has_agv1();
  void set_has_agv2();
  void clear_has_agv2();

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::google::protobuf::int32 agv1_;
  ::google::protobuf::int32 agv2_;
  friend struct ::protobuf_Protbload_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class RESULT : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Protbload.RESULT) */ {
 public:
  RESULT();
  virtual ~RESULT();

  RESULT(const RESULT& from);

  inline RESULT& operator=(const RESULT& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  RESULT(RESULT&& from) noexcept
    : RESULT() {
    *this = ::std::move(from);
  }

  inline RESULT& operator=(RESULT&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const RESULT& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const RESULT* internal_default_instance() {
    return reinterpret_cast<const RESULT*>(
               &_RESULT_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(RESULT* other);
  friend void swap(RESULT& a, RESULT& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline RESULT* New() const final {
    return CreateMaybeMessage<RESULT>(NULL);
  }

  RESULT* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<RESULT>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const RESULT& from);
  void MergeFrom(const RESULT& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(RESULT* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 answer = 1;
  bool has_answer() const;
  void clear_answer();
  static const int kAnswerFieldNumber = 1;
  ::google::protobuf::int32 answer() const;
  void set_answer(::google::protobuf::int32 value);

  // optional bool exflag = 2 [default = false];
  bool has_exflag() const;
  void clear_exflag();
  static const int kExflagFieldNumber = 2;
  bool exflag() const;
  void set_exflag(bool value);

  // @@protoc_insertion_point(class_scope:Protbload.RESULT)
 private:
  void set_has_answer();
  void clear_has_answer();
  void set_has_exflag();
  void clear_has_exflag();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::google::protobuf::int32 answer_;
  bool exflag_;
  friend struct ::protobuf_Protbload_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// ADD

// required int32 agv1 = 1;
inline bool ADD::has_agv1() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ADD::set_has_agv1() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ADD::clear_has_agv1() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ADD::clear_agv1() {
  agv1_ = 0;
  clear_has_agv1();
}
inline ::google::protobuf::int32 ADD::agv1() const {
  // @@protoc_insertion_point(field_get:Protbload.ADD.agv1)
  return agv1_;
}
inline void ADD::set_agv1(::google::protobuf::int32 value) {
  set_has_agv1();
  agv1_ = value;
  // @@protoc_insertion_point(field_set:Protbload.ADD.agv1)
}

// required int32 agv2 = 2;
inline bool ADD::has_agv2() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ADD::set_has_agv2() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ADD::clear_has_agv2() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ADD::clear_agv2() {
  agv2_ = 0;
  clear_has_agv2();
}
inline ::google::protobuf::int32 ADD::agv2() const {
  // @@protoc_insertion_point(field_get:Protbload.ADD.agv2)
  return agv2_;
}
inline void ADD::set_agv2(::google::protobuf::int32 value) {
  set_has_agv2();
  agv2_ = value;
  // @@protoc_insertion_point(field_set:Protbload.ADD.agv2)
}

// -------------------------------------------------------------------

// RESULT

// required int32 answer = 1;
inline bool RESULT::has_answer() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void RESULT::set_has_answer() {
  _has_bits_[0] |= 0x00000001u;
}
inline void RESULT::clear_has_answer() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void RESULT::clear_answer() {
  answer_ = 0;
  clear_has_answer();
}
inline ::google::protobuf::int32 RESULT::answer() const {
  // @@protoc_insertion_point(field_get:Protbload.RESULT.answer)
  return answer_;
}
inline void RESULT::set_answer(::google::protobuf::int32 value) {
  set_has_answer();
  answer_ = value;
  // @@protoc_insertion_point(field_set:Protbload.RESULT.answer)
}

// optional bool exflag = 2 [default = false];
inline bool RESULT::has_exflag() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void RESULT::set_has_exflag() {
  _has_bits_[0] |= 0x00000002u;
}
inline void RESULT::clear_has_exflag() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void RESULT::clear_exflag() {
  exflag_ = false;
  clear_has_exflag();
}
inline bool RESULT::exflag() const {
  // @@protoc_insertion_point(field_get:Protbload.RESULT.exflag)
  return exflag_;
}
inline void RESULT::set_exflag(bool value) {
  set_has_exflag();
  exflag_ = value;
  // @@protoc_insertion_point(field_set:Protbload.RESULT.exflag)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace Protbload

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_Protbload_2eproto