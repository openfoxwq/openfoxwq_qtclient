// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: proto/reqOption.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_proto_2freqOption_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_proto_2freqOption_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021012 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include <google/protobuf/descriptor.pb.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_proto_2freqOption_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_proto_2freqOption_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_proto_2freqOption_2eproto;
namespace openfoxwq {
class MessageHeader;
struct MessageHeaderDefaultTypeInternal;
extern MessageHeaderDefaultTypeInternal _MessageHeader_default_instance_;
class MessageTag;
struct MessageTagDefaultTypeInternal;
extern MessageTagDefaultTypeInternal _MessageTag_default_instance_;
}  // namespace openfoxwq
PROTOBUF_NAMESPACE_OPEN
template<> ::openfoxwq::MessageHeader* Arena::CreateMaybeMessage<::openfoxwq::MessageHeader>(Arena*);
template<> ::openfoxwq::MessageTag* Arena::CreateMaybeMessage<::openfoxwq::MessageTag>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace openfoxwq {

// ===================================================================

class MessageTag final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:openfoxwq.MessageTag) */ {
 public:
  inline MessageTag() : MessageTag(nullptr) {}
  ~MessageTag() override;
  explicit PROTOBUF_CONSTEXPR MessageTag(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  MessageTag(const MessageTag& from);
  MessageTag(MessageTag&& from) noexcept
    : MessageTag() {
    *this = ::std::move(from);
  }

  inline MessageTag& operator=(const MessageTag& from) {
    CopyFrom(from);
    return *this;
  }
  inline MessageTag& operator=(MessageTag&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const MessageTag& default_instance() {
    return *internal_default_instance();
  }
  static inline const MessageTag* internal_default_instance() {
    return reinterpret_cast<const MessageTag*>(
               &_MessageTag_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(MessageTag& a, MessageTag& b) {
    a.Swap(&b);
  }
  inline void Swap(MessageTag* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(MessageTag* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  MessageTag* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<MessageTag>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const MessageTag& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const MessageTag& from) {
    MessageTag::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(MessageTag* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "openfoxwq.MessageTag";
  }
  protected:
  explicit MessageTag(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kHeaderFieldNumber = 3,
    kReqFieldNumber = 1,
    kRespFieldNumber = 2,
  };
  // optional .openfoxwq.MessageHeader header = 3;
  bool has_header() const;
  private:
  bool _internal_has_header() const;
  public:
  void clear_header();
  const ::openfoxwq::MessageHeader& header() const;
  PROTOBUF_NODISCARD ::openfoxwq::MessageHeader* release_header();
  ::openfoxwq::MessageHeader* mutable_header();
  void set_allocated_header(::openfoxwq::MessageHeader* header);
  private:
  const ::openfoxwq::MessageHeader& _internal_header() const;
  ::openfoxwq::MessageHeader* _internal_mutable_header();
  public:
  void unsafe_arena_set_allocated_header(
      ::openfoxwq::MessageHeader* header);
  ::openfoxwq::MessageHeader* unsafe_arena_release_header();

  // optional uint32 req = 1;
  bool has_req() const;
  private:
  bool _internal_has_req() const;
  public:
  void clear_req();
  uint32_t req() const;
  void set_req(uint32_t value);
  private:
  uint32_t _internal_req() const;
  void _internal_set_req(uint32_t value);
  public:

  // optional uint32 resp = 2;
  bool has_resp() const;
  private:
  bool _internal_has_resp() const;
  public:
  void clear_resp();
  uint32_t resp() const;
  void set_resp(uint32_t value);
  private:
  uint32_t _internal_resp() const;
  void _internal_set_resp(uint32_t value);
  public:

  // @@protoc_insertion_point(class_scope:openfoxwq.MessageTag)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
    ::openfoxwq::MessageHeader* header_;
    uint32_t req_;
    uint32_t resp_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_proto_2freqOption_2eproto;
};
// -------------------------------------------------------------------

class MessageHeader final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:openfoxwq.MessageHeader) */ {
 public:
  inline MessageHeader() : MessageHeader(nullptr) {}
  ~MessageHeader() override;
  explicit PROTOBUF_CONSTEXPR MessageHeader(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  MessageHeader(const MessageHeader& from);
  MessageHeader(MessageHeader&& from) noexcept
    : MessageHeader() {
    *this = ::std::move(from);
  }

  inline MessageHeader& operator=(const MessageHeader& from) {
    CopyFrom(from);
    return *this;
  }
  inline MessageHeader& operator=(MessageHeader&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const MessageHeader& default_instance() {
    return *internal_default_instance();
  }
  static inline const MessageHeader* internal_default_instance() {
    return reinterpret_cast<const MessageHeader*>(
               &_MessageHeader_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(MessageHeader& a, MessageHeader& b) {
    a.Swap(&b);
  }
  inline void Swap(MessageHeader* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(MessageHeader* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  MessageHeader* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<MessageHeader>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const MessageHeader& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const MessageHeader& from) {
    MessageHeader::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(MessageHeader* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "openfoxwq.MessageHeader";
  }
  protected:
  explicit MessageHeader(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kUnknownField13FieldNumber = 13,
    kUnknownField2FieldNumber = 2,
    kPlayerIdFieldNumber = 3,
    kUnknownField4FieldNumber = 4,
    kTag1FieldNumber = 1,
    kTag2FieldNumber = 7,
    kUnknownField5FieldNumber = 5,
    kUnknownField6FieldNumber = 6,
    kUnknownField8FieldNumber = 8,
    kUnknownField9FieldNumber = 9,
    kUnknownField12FieldNumber = 12,
    kUnknownField15FieldNumber = 15,
  };
  // optional string unknown_field_13 = 13;
  bool has_unknown_field_13() const;
  private:
  bool _internal_has_unknown_field_13() const;
  public:
  void clear_unknown_field_13();
  const std::string& unknown_field_13() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_unknown_field_13(ArgT0&& arg0, ArgT... args);
  std::string* mutable_unknown_field_13();
  PROTOBUF_NODISCARD std::string* release_unknown_field_13();
  void set_allocated_unknown_field_13(std::string* unknown_field_13);
  private:
  const std::string& _internal_unknown_field_13() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_unknown_field_13(const std::string& value);
  std::string* _internal_mutable_unknown_field_13();
  public:

  // optional int64 unknown_field_2 = 2;
  bool has_unknown_field_2() const;
  private:
  bool _internal_has_unknown_field_2() const;
  public:
  void clear_unknown_field_2();
  int64_t unknown_field_2() const;
  void set_unknown_field_2(int64_t value);
  private:
  int64_t _internal_unknown_field_2() const;
  void _internal_set_unknown_field_2(int64_t value);
  public:

  // optional int64 player_id = 3;
  bool has_player_id() const;
  private:
  bool _internal_has_player_id() const;
  public:
  void clear_player_id();
  int64_t player_id() const;
  void set_player_id(int64_t value);
  private:
  int64_t _internal_player_id() const;
  void _internal_set_player_id(int64_t value);
  public:

  // optional int64 unknown_field_4 = 4;
  bool has_unknown_field_4() const;
  private:
  bool _internal_has_unknown_field_4() const;
  public:
  void clear_unknown_field_4();
  int64_t unknown_field_4() const;
  void set_unknown_field_4(int64_t value);
  private:
  int64_t _internal_unknown_field_4() const;
  void _internal_set_unknown_field_4(int64_t value);
  public:

  // required uint32 tag1 = 1;
  bool has_tag1() const;
  private:
  bool _internal_has_tag1() const;
  public:
  void clear_tag1();
  uint32_t tag1() const;
  void set_tag1(uint32_t value);
  private:
  uint32_t _internal_tag1() const;
  void _internal_set_tag1(uint32_t value);
  public:

  // required uint32 tag2 = 7;
  bool has_tag2() const;
  private:
  bool _internal_has_tag2() const;
  public:
  void clear_tag2();
  uint32_t tag2() const;
  void set_tag2(uint32_t value);
  private:
  uint32_t _internal_tag2() const;
  void _internal_set_tag2(uint32_t value);
  public:

  // optional int64 unknown_field_5 = 5;
  bool has_unknown_field_5() const;
  private:
  bool _internal_has_unknown_field_5() const;
  public:
  void clear_unknown_field_5();
  int64_t unknown_field_5() const;
  void set_unknown_field_5(int64_t value);
  private:
  int64_t _internal_unknown_field_5() const;
  void _internal_set_unknown_field_5(int64_t value);
  public:

  // optional int64 unknown_field_6 = 6;
  bool has_unknown_field_6() const;
  private:
  bool _internal_has_unknown_field_6() const;
  public:
  void clear_unknown_field_6();
  int64_t unknown_field_6() const;
  void set_unknown_field_6(int64_t value);
  private:
  int64_t _internal_unknown_field_6() const;
  void _internal_set_unknown_field_6(int64_t value);
  public:

  // optional int64 unknown_field_8 = 8;
  bool has_unknown_field_8() const;
  private:
  bool _internal_has_unknown_field_8() const;
  public:
  void clear_unknown_field_8();
  int64_t unknown_field_8() const;
  void set_unknown_field_8(int64_t value);
  private:
  int64_t _internal_unknown_field_8() const;
  void _internal_set_unknown_field_8(int64_t value);
  public:

  // optional int64 unknown_field_9 = 9;
  bool has_unknown_field_9() const;
  private:
  bool _internal_has_unknown_field_9() const;
  public:
  void clear_unknown_field_9();
  int64_t unknown_field_9() const;
  void set_unknown_field_9(int64_t value);
  private:
  int64_t _internal_unknown_field_9() const;
  void _internal_set_unknown_field_9(int64_t value);
  public:

  // optional int64 unknown_field_12 = 12;
  bool has_unknown_field_12() const;
  private:
  bool _internal_has_unknown_field_12() const;
  public:
  void clear_unknown_field_12();
  int64_t unknown_field_12() const;
  void set_unknown_field_12(int64_t value);
  private:
  int64_t _internal_unknown_field_12() const;
  void _internal_set_unknown_field_12(int64_t value);
  public:

  // optional int64 unknown_field_15 = 15;
  bool has_unknown_field_15() const;
  private:
  bool _internal_has_unknown_field_15() const;
  public:
  void clear_unknown_field_15();
  int64_t unknown_field_15() const;
  void set_unknown_field_15(int64_t value);
  private:
  int64_t _internal_unknown_field_15() const;
  void _internal_set_unknown_field_15(int64_t value);
  public:

  // @@protoc_insertion_point(class_scope:openfoxwq.MessageHeader)
 private:
  class _Internal;

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr unknown_field_13_;
    int64_t unknown_field_2_;
    int64_t player_id_;
    int64_t unknown_field_4_;
    uint32_t tag1_;
    uint32_t tag2_;
    int64_t unknown_field_5_;
    int64_t unknown_field_6_;
    int64_t unknown_field_8_;
    int64_t unknown_field_9_;
    int64_t unknown_field_12_;
    int64_t unknown_field_15_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_proto_2freqOption_2eproto;
};
// ===================================================================

static const int kMsgTagFieldNumber = 50000;
extern ::PROTOBUF_NAMESPACE_ID::internal::ExtensionIdentifier< ::PROTOBUF_NAMESPACE_ID::MethodOptions,
    ::PROTOBUF_NAMESPACE_ID::internal::MessageTypeTraits< ::openfoxwq::MessageTag >, 11, false >
  msg_tag;

// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// MessageTag

// optional uint32 req = 1;
inline bool MessageTag::_internal_has_req() const {
  bool value = (_impl_._has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool MessageTag::has_req() const {
  return _internal_has_req();
}
inline void MessageTag::clear_req() {
  _impl_.req_ = 0u;
  _impl_._has_bits_[0] &= ~0x00000002u;
}
inline uint32_t MessageTag::_internal_req() const {
  return _impl_.req_;
}
inline uint32_t MessageTag::req() const {
  // @@protoc_insertion_point(field_get:openfoxwq.MessageTag.req)
  return _internal_req();
}
inline void MessageTag::_internal_set_req(uint32_t value) {
  _impl_._has_bits_[0] |= 0x00000002u;
  _impl_.req_ = value;
}
inline void MessageTag::set_req(uint32_t value) {
  _internal_set_req(value);
  // @@protoc_insertion_point(field_set:openfoxwq.MessageTag.req)
}

// optional uint32 resp = 2;
inline bool MessageTag::_internal_has_resp() const {
  bool value = (_impl_._has_bits_[0] & 0x00000004u) != 0;
  return value;
}
inline bool MessageTag::has_resp() const {
  return _internal_has_resp();
}
inline void MessageTag::clear_resp() {
  _impl_.resp_ = 0u;
  _impl_._has_bits_[0] &= ~0x00000004u;
}
inline uint32_t MessageTag::_internal_resp() const {
  return _impl_.resp_;
}
inline uint32_t MessageTag::resp() const {
  // @@protoc_insertion_point(field_get:openfoxwq.MessageTag.resp)
  return _internal_resp();
}
inline void MessageTag::_internal_set_resp(uint32_t value) {
  _impl_._has_bits_[0] |= 0x00000004u;
  _impl_.resp_ = value;
}
inline void MessageTag::set_resp(uint32_t value) {
  _internal_set_resp(value);
  // @@protoc_insertion_point(field_set:openfoxwq.MessageTag.resp)
}

// optional .openfoxwq.MessageHeader header = 3;
inline bool MessageTag::_internal_has_header() const {
  bool value = (_impl_._has_bits_[0] & 0x00000001u) != 0;
  PROTOBUF_ASSUME(!value || _impl_.header_ != nullptr);
  return value;
}
inline bool MessageTag::has_header() const {
  return _internal_has_header();
}
inline void MessageTag::clear_header() {
  if (_impl_.header_ != nullptr) _impl_.header_->Clear();
  _impl_._has_bits_[0] &= ~0x00000001u;
}
inline const ::openfoxwq::MessageHeader& MessageTag::_internal_header() const {
  const ::openfoxwq::MessageHeader* p = _impl_.header_;
  return p != nullptr ? *p : reinterpret_cast<const ::openfoxwq::MessageHeader&>(
      ::openfoxwq::_MessageHeader_default_instance_);
}
inline const ::openfoxwq::MessageHeader& MessageTag::header() const {
  // @@protoc_insertion_point(field_get:openfoxwq.MessageTag.header)
  return _internal_header();
}
inline void MessageTag::unsafe_arena_set_allocated_header(
    ::openfoxwq::MessageHeader* header) {
  if (GetArenaForAllocation() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(_impl_.header_);
  }
  _impl_.header_ = header;
  if (header) {
    _impl_._has_bits_[0] |= 0x00000001u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000001u;
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:openfoxwq.MessageTag.header)
}
inline ::openfoxwq::MessageHeader* MessageTag::release_header() {
  _impl_._has_bits_[0] &= ~0x00000001u;
  ::openfoxwq::MessageHeader* temp = _impl_.header_;
  _impl_.header_ = nullptr;
#ifdef PROTOBUF_FORCE_COPY_IN_RELEASE
  auto* old =  reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(temp);
  temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  if (GetArenaForAllocation() == nullptr) { delete old; }
#else  // PROTOBUF_FORCE_COPY_IN_RELEASE
  if (GetArenaForAllocation() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
#endif  // !PROTOBUF_FORCE_COPY_IN_RELEASE
  return temp;
}
inline ::openfoxwq::MessageHeader* MessageTag::unsafe_arena_release_header() {
  // @@protoc_insertion_point(field_release:openfoxwq.MessageTag.header)
  _impl_._has_bits_[0] &= ~0x00000001u;
  ::openfoxwq::MessageHeader* temp = _impl_.header_;
  _impl_.header_ = nullptr;
  return temp;
}
inline ::openfoxwq::MessageHeader* MessageTag::_internal_mutable_header() {
  _impl_._has_bits_[0] |= 0x00000001u;
  if (_impl_.header_ == nullptr) {
    auto* p = CreateMaybeMessage<::openfoxwq::MessageHeader>(GetArenaForAllocation());
    _impl_.header_ = p;
  }
  return _impl_.header_;
}
inline ::openfoxwq::MessageHeader* MessageTag::mutable_header() {
  ::openfoxwq::MessageHeader* _msg = _internal_mutable_header();
  // @@protoc_insertion_point(field_mutable:openfoxwq.MessageTag.header)
  return _msg;
}
inline void MessageTag::set_allocated_header(::openfoxwq::MessageHeader* header) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  if (message_arena == nullptr) {
    delete _impl_.header_;
  }
  if (header) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
        ::PROTOBUF_NAMESPACE_ID::Arena::InternalGetOwningArena(header);
    if (message_arena != submessage_arena) {
      header = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, header, submessage_arena);
    }
    _impl_._has_bits_[0] |= 0x00000001u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000001u;
  }
  _impl_.header_ = header;
  // @@protoc_insertion_point(field_set_allocated:openfoxwq.MessageTag.header)
}

// -------------------------------------------------------------------

// MessageHeader

// required uint32 tag1 = 1;
inline bool MessageHeader::_internal_has_tag1() const {
  bool value = (_impl_._has_bits_[0] & 0x00000010u) != 0;
  return value;
}
inline bool MessageHeader::has_tag1() const {
  return _internal_has_tag1();
}
inline void MessageHeader::clear_tag1() {
  _impl_.tag1_ = 0u;
  _impl_._has_bits_[0] &= ~0x00000010u;
}
inline uint32_t MessageHeader::_internal_tag1() const {
  return _impl_.tag1_;
}
inline uint32_t MessageHeader::tag1() const {
  // @@protoc_insertion_point(field_get:openfoxwq.MessageHeader.tag1)
  return _internal_tag1();
}
inline void MessageHeader::_internal_set_tag1(uint32_t value) {
  _impl_._has_bits_[0] |= 0x00000010u;
  _impl_.tag1_ = value;
}
inline void MessageHeader::set_tag1(uint32_t value) {
  _internal_set_tag1(value);
  // @@protoc_insertion_point(field_set:openfoxwq.MessageHeader.tag1)
}

// required uint32 tag2 = 7;
inline bool MessageHeader::_internal_has_tag2() const {
  bool value = (_impl_._has_bits_[0] & 0x00000020u) != 0;
  return value;
}
inline bool MessageHeader::has_tag2() const {
  return _internal_has_tag2();
}
inline void MessageHeader::clear_tag2() {
  _impl_.tag2_ = 0u;
  _impl_._has_bits_[0] &= ~0x00000020u;
}
inline uint32_t MessageHeader::_internal_tag2() const {
  return _impl_.tag2_;
}
inline uint32_t MessageHeader::tag2() const {
  // @@protoc_insertion_point(field_get:openfoxwq.MessageHeader.tag2)
  return _internal_tag2();
}
inline void MessageHeader::_internal_set_tag2(uint32_t value) {
  _impl_._has_bits_[0] |= 0x00000020u;
  _impl_.tag2_ = value;
}
inline void MessageHeader::set_tag2(uint32_t value) {
  _internal_set_tag2(value);
  // @@protoc_insertion_point(field_set:openfoxwq.MessageHeader.tag2)
}

// optional int64 player_id = 3;
inline bool MessageHeader::_internal_has_player_id() const {
  bool value = (_impl_._has_bits_[0] & 0x00000004u) != 0;
  return value;
}
inline bool MessageHeader::has_player_id() const {
  return _internal_has_player_id();
}
inline void MessageHeader::clear_player_id() {
  _impl_.player_id_ = int64_t{0};
  _impl_._has_bits_[0] &= ~0x00000004u;
}
inline int64_t MessageHeader::_internal_player_id() const {
  return _impl_.player_id_;
}
inline int64_t MessageHeader::player_id() const {
  // @@protoc_insertion_point(field_get:openfoxwq.MessageHeader.player_id)
  return _internal_player_id();
}
inline void MessageHeader::_internal_set_player_id(int64_t value) {
  _impl_._has_bits_[0] |= 0x00000004u;
  _impl_.player_id_ = value;
}
inline void MessageHeader::set_player_id(int64_t value) {
  _internal_set_player_id(value);
  // @@protoc_insertion_point(field_set:openfoxwq.MessageHeader.player_id)
}

// optional int64 unknown_field_2 = 2;
inline bool MessageHeader::_internal_has_unknown_field_2() const {
  bool value = (_impl_._has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool MessageHeader::has_unknown_field_2() const {
  return _internal_has_unknown_field_2();
}
inline void MessageHeader::clear_unknown_field_2() {
  _impl_.unknown_field_2_ = int64_t{0};
  _impl_._has_bits_[0] &= ~0x00000002u;
}
inline int64_t MessageHeader::_internal_unknown_field_2() const {
  return _impl_.unknown_field_2_;
}
inline int64_t MessageHeader::unknown_field_2() const {
  // @@protoc_insertion_point(field_get:openfoxwq.MessageHeader.unknown_field_2)
  return _internal_unknown_field_2();
}
inline void MessageHeader::_internal_set_unknown_field_2(int64_t value) {
  _impl_._has_bits_[0] |= 0x00000002u;
  _impl_.unknown_field_2_ = value;
}
inline void MessageHeader::set_unknown_field_2(int64_t value) {
  _internal_set_unknown_field_2(value);
  // @@protoc_insertion_point(field_set:openfoxwq.MessageHeader.unknown_field_2)
}

// optional int64 unknown_field_4 = 4;
inline bool MessageHeader::_internal_has_unknown_field_4() const {
  bool value = (_impl_._has_bits_[0] & 0x00000008u) != 0;
  return value;
}
inline bool MessageHeader::has_unknown_field_4() const {
  return _internal_has_unknown_field_4();
}
inline void MessageHeader::clear_unknown_field_4() {
  _impl_.unknown_field_4_ = int64_t{0};
  _impl_._has_bits_[0] &= ~0x00000008u;
}
inline int64_t MessageHeader::_internal_unknown_field_4() const {
  return _impl_.unknown_field_4_;
}
inline int64_t MessageHeader::unknown_field_4() const {
  // @@protoc_insertion_point(field_get:openfoxwq.MessageHeader.unknown_field_4)
  return _internal_unknown_field_4();
}
inline void MessageHeader::_internal_set_unknown_field_4(int64_t value) {
  _impl_._has_bits_[0] |= 0x00000008u;
  _impl_.unknown_field_4_ = value;
}
inline void MessageHeader::set_unknown_field_4(int64_t value) {
  _internal_set_unknown_field_4(value);
  // @@protoc_insertion_point(field_set:openfoxwq.MessageHeader.unknown_field_4)
}

// optional int64 unknown_field_5 = 5;
inline bool MessageHeader::_internal_has_unknown_field_5() const {
  bool value = (_impl_._has_bits_[0] & 0x00000040u) != 0;
  return value;
}
inline bool MessageHeader::has_unknown_field_5() const {
  return _internal_has_unknown_field_5();
}
inline void MessageHeader::clear_unknown_field_5() {
  _impl_.unknown_field_5_ = int64_t{0};
  _impl_._has_bits_[0] &= ~0x00000040u;
}
inline int64_t MessageHeader::_internal_unknown_field_5() const {
  return _impl_.unknown_field_5_;
}
inline int64_t MessageHeader::unknown_field_5() const {
  // @@protoc_insertion_point(field_get:openfoxwq.MessageHeader.unknown_field_5)
  return _internal_unknown_field_5();
}
inline void MessageHeader::_internal_set_unknown_field_5(int64_t value) {
  _impl_._has_bits_[0] |= 0x00000040u;
  _impl_.unknown_field_5_ = value;
}
inline void MessageHeader::set_unknown_field_5(int64_t value) {
  _internal_set_unknown_field_5(value);
  // @@protoc_insertion_point(field_set:openfoxwq.MessageHeader.unknown_field_5)
}

// optional int64 unknown_field_6 = 6;
inline bool MessageHeader::_internal_has_unknown_field_6() const {
  bool value = (_impl_._has_bits_[0] & 0x00000080u) != 0;
  return value;
}
inline bool MessageHeader::has_unknown_field_6() const {
  return _internal_has_unknown_field_6();
}
inline void MessageHeader::clear_unknown_field_6() {
  _impl_.unknown_field_6_ = int64_t{0};
  _impl_._has_bits_[0] &= ~0x00000080u;
}
inline int64_t MessageHeader::_internal_unknown_field_6() const {
  return _impl_.unknown_field_6_;
}
inline int64_t MessageHeader::unknown_field_6() const {
  // @@protoc_insertion_point(field_get:openfoxwq.MessageHeader.unknown_field_6)
  return _internal_unknown_field_6();
}
inline void MessageHeader::_internal_set_unknown_field_6(int64_t value) {
  _impl_._has_bits_[0] |= 0x00000080u;
  _impl_.unknown_field_6_ = value;
}
inline void MessageHeader::set_unknown_field_6(int64_t value) {
  _internal_set_unknown_field_6(value);
  // @@protoc_insertion_point(field_set:openfoxwq.MessageHeader.unknown_field_6)
}

// optional int64 unknown_field_8 = 8;
inline bool MessageHeader::_internal_has_unknown_field_8() const {
  bool value = (_impl_._has_bits_[0] & 0x00000100u) != 0;
  return value;
}
inline bool MessageHeader::has_unknown_field_8() const {
  return _internal_has_unknown_field_8();
}
inline void MessageHeader::clear_unknown_field_8() {
  _impl_.unknown_field_8_ = int64_t{0};
  _impl_._has_bits_[0] &= ~0x00000100u;
}
inline int64_t MessageHeader::_internal_unknown_field_8() const {
  return _impl_.unknown_field_8_;
}
inline int64_t MessageHeader::unknown_field_8() const {
  // @@protoc_insertion_point(field_get:openfoxwq.MessageHeader.unknown_field_8)
  return _internal_unknown_field_8();
}
inline void MessageHeader::_internal_set_unknown_field_8(int64_t value) {
  _impl_._has_bits_[0] |= 0x00000100u;
  _impl_.unknown_field_8_ = value;
}
inline void MessageHeader::set_unknown_field_8(int64_t value) {
  _internal_set_unknown_field_8(value);
  // @@protoc_insertion_point(field_set:openfoxwq.MessageHeader.unknown_field_8)
}

// optional int64 unknown_field_9 = 9;
inline bool MessageHeader::_internal_has_unknown_field_9() const {
  bool value = (_impl_._has_bits_[0] & 0x00000200u) != 0;
  return value;
}
inline bool MessageHeader::has_unknown_field_9() const {
  return _internal_has_unknown_field_9();
}
inline void MessageHeader::clear_unknown_field_9() {
  _impl_.unknown_field_9_ = int64_t{0};
  _impl_._has_bits_[0] &= ~0x00000200u;
}
inline int64_t MessageHeader::_internal_unknown_field_9() const {
  return _impl_.unknown_field_9_;
}
inline int64_t MessageHeader::unknown_field_9() const {
  // @@protoc_insertion_point(field_get:openfoxwq.MessageHeader.unknown_field_9)
  return _internal_unknown_field_9();
}
inline void MessageHeader::_internal_set_unknown_field_9(int64_t value) {
  _impl_._has_bits_[0] |= 0x00000200u;
  _impl_.unknown_field_9_ = value;
}
inline void MessageHeader::set_unknown_field_9(int64_t value) {
  _internal_set_unknown_field_9(value);
  // @@protoc_insertion_point(field_set:openfoxwq.MessageHeader.unknown_field_9)
}

// optional int64 unknown_field_12 = 12;
inline bool MessageHeader::_internal_has_unknown_field_12() const {
  bool value = (_impl_._has_bits_[0] & 0x00000400u) != 0;
  return value;
}
inline bool MessageHeader::has_unknown_field_12() const {
  return _internal_has_unknown_field_12();
}
inline void MessageHeader::clear_unknown_field_12() {
  _impl_.unknown_field_12_ = int64_t{0};
  _impl_._has_bits_[0] &= ~0x00000400u;
}
inline int64_t MessageHeader::_internal_unknown_field_12() const {
  return _impl_.unknown_field_12_;
}
inline int64_t MessageHeader::unknown_field_12() const {
  // @@protoc_insertion_point(field_get:openfoxwq.MessageHeader.unknown_field_12)
  return _internal_unknown_field_12();
}
inline void MessageHeader::_internal_set_unknown_field_12(int64_t value) {
  _impl_._has_bits_[0] |= 0x00000400u;
  _impl_.unknown_field_12_ = value;
}
inline void MessageHeader::set_unknown_field_12(int64_t value) {
  _internal_set_unknown_field_12(value);
  // @@protoc_insertion_point(field_set:openfoxwq.MessageHeader.unknown_field_12)
}

// optional string unknown_field_13 = 13;
inline bool MessageHeader::_internal_has_unknown_field_13() const {
  bool value = (_impl_._has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool MessageHeader::has_unknown_field_13() const {
  return _internal_has_unknown_field_13();
}
inline void MessageHeader::clear_unknown_field_13() {
  _impl_.unknown_field_13_.ClearToEmpty();
  _impl_._has_bits_[0] &= ~0x00000001u;
}
inline const std::string& MessageHeader::unknown_field_13() const {
  // @@protoc_insertion_point(field_get:openfoxwq.MessageHeader.unknown_field_13)
  return _internal_unknown_field_13();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void MessageHeader::set_unknown_field_13(ArgT0&& arg0, ArgT... args) {
 _impl_._has_bits_[0] |= 0x00000001u;
 _impl_.unknown_field_13_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:openfoxwq.MessageHeader.unknown_field_13)
}
inline std::string* MessageHeader::mutable_unknown_field_13() {
  std::string* _s = _internal_mutable_unknown_field_13();
  // @@protoc_insertion_point(field_mutable:openfoxwq.MessageHeader.unknown_field_13)
  return _s;
}
inline const std::string& MessageHeader::_internal_unknown_field_13() const {
  return _impl_.unknown_field_13_.Get();
}
inline void MessageHeader::_internal_set_unknown_field_13(const std::string& value) {
  _impl_._has_bits_[0] |= 0x00000001u;
  _impl_.unknown_field_13_.Set(value, GetArenaForAllocation());
}
inline std::string* MessageHeader::_internal_mutable_unknown_field_13() {
  _impl_._has_bits_[0] |= 0x00000001u;
  return _impl_.unknown_field_13_.Mutable(GetArenaForAllocation());
}
inline std::string* MessageHeader::release_unknown_field_13() {
  // @@protoc_insertion_point(field_release:openfoxwq.MessageHeader.unknown_field_13)
  if (!_internal_has_unknown_field_13()) {
    return nullptr;
  }
  _impl_._has_bits_[0] &= ~0x00000001u;
  auto* p = _impl_.unknown_field_13_.Release();
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.unknown_field_13_.IsDefault()) {
    _impl_.unknown_field_13_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  return p;
}
inline void MessageHeader::set_allocated_unknown_field_13(std::string* unknown_field_13) {
  if (unknown_field_13 != nullptr) {
    _impl_._has_bits_[0] |= 0x00000001u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000001u;
  }
  _impl_.unknown_field_13_.SetAllocated(unknown_field_13, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.unknown_field_13_.IsDefault()) {
    _impl_.unknown_field_13_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:openfoxwq.MessageHeader.unknown_field_13)
}

// optional int64 unknown_field_15 = 15;
inline bool MessageHeader::_internal_has_unknown_field_15() const {
  bool value = (_impl_._has_bits_[0] & 0x00000800u) != 0;
  return value;
}
inline bool MessageHeader::has_unknown_field_15() const {
  return _internal_has_unknown_field_15();
}
inline void MessageHeader::clear_unknown_field_15() {
  _impl_.unknown_field_15_ = int64_t{0};
  _impl_._has_bits_[0] &= ~0x00000800u;
}
inline int64_t MessageHeader::_internal_unknown_field_15() const {
  return _impl_.unknown_field_15_;
}
inline int64_t MessageHeader::unknown_field_15() const {
  // @@protoc_insertion_point(field_get:openfoxwq.MessageHeader.unknown_field_15)
  return _internal_unknown_field_15();
}
inline void MessageHeader::_internal_set_unknown_field_15(int64_t value) {
  _impl_._has_bits_[0] |= 0x00000800u;
  _impl_.unknown_field_15_ = value;
}
inline void MessageHeader::set_unknown_field_15(int64_t value) {
  _internal_set_unknown_field_15(value);
  // @@protoc_insertion_point(field_set:openfoxwq.MessageHeader.unknown_field_15)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace openfoxwq

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_proto_2freqOption_2eproto
