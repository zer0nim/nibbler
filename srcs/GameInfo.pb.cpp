// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: gameInfo.proto

#include "GameInfo.pb.hpp"

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
extern PROTOBUF_INTERNAL_EXPORT_gameInfo_2eproto ::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_IVec2_gameInfo_2eproto;
extern PROTOBUF_INTERNAL_EXPORT_gameInfo_2eproto ::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<1> scc_info_Snake_gameInfo_2eproto;
namespace gameInfoProto {
class IVec2DefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<IVec2> _instance;
} _IVec2_default_instance_;
class SnakeDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<Snake> _instance;
} _Snake_default_instance_;
class GameInfoDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<GameInfo> _instance;
} _GameInfo_default_instance_;
}  // namespace gameInfoProto
static void InitDefaultsscc_info_GameInfo_gameInfo_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::gameInfoProto::_GameInfo_default_instance_;
    new (ptr) ::gameInfoProto::GameInfo();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::gameInfoProto::GameInfo::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<2> scc_info_GameInfo_gameInfo_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 2, 0, InitDefaultsscc_info_GameInfo_gameInfo_2eproto}, {
      &scc_info_IVec2_gameInfo_2eproto.base,
      &scc_info_Snake_gameInfo_2eproto.base,}};

static void InitDefaultsscc_info_IVec2_gameInfo_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::gameInfoProto::_IVec2_default_instance_;
    new (ptr) ::gameInfoProto::IVec2();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::gameInfoProto::IVec2::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_IVec2_gameInfo_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_IVec2_gameInfo_2eproto}, {}};

static void InitDefaultsscc_info_Snake_gameInfo_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::gameInfoProto::_Snake_default_instance_;
    new (ptr) ::gameInfoProto::Snake();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::gameInfoProto::Snake::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<1> scc_info_Snake_gameInfo_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 1, 0, InitDefaultsscc_info_Snake_gameInfo_2eproto}, {
      &scc_info_IVec2_gameInfo_2eproto.base,}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_gameInfo_2eproto[3];
static const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* file_level_enum_descriptors_gameInfo_2eproto[2];
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_gameInfo_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_gameInfo_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::gameInfoProto::IVec2, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::gameInfoProto::IVec2, x_),
  PROTOBUF_FIELD_OFFSET(::gameInfoProto::IVec2, y_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::gameInfoProto::Snake, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::gameInfoProto::Snake, body_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::gameInfoProto::GameInfo, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::gameInfoProto::GameInfo, food_),
  PROTOBUF_FIELD_OFFSET(::gameInfoProto::GameInfo, play_),
  PROTOBUF_FIELD_OFFSET(::gameInfoProto::GameInfo, snake_),
  PROTOBUF_FIELD_OFFSET(::gameInfoProto::GameInfo, snakeop_),
  PROTOBUF_FIELD_OFFSET(::gameInfoProto::GameInfo, snakespeed_),
  PROTOBUF_FIELD_OFFSET(::gameInfoProto::GameInfo, direction_),
  PROTOBUF_FIELD_OFFSET(::gameInfoProto::GameInfo, quitted_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::gameInfoProto::IVec2)},
  { 7, -1, sizeof(::gameInfoProto::Snake)},
  { 13, -1, sizeof(::gameInfoProto::GameInfo)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::gameInfoProto::_IVec2_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::gameInfoProto::_Snake_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::gameInfoProto::_GameInfo_default_instance_),
};

const char descriptor_table_protodef_gameInfo_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\016gameInfo.proto\022\rgameInfoProto\"\035\n\005IVec2"
  "\022\t\n\001x\030\001 \001(\r\022\t\n\001y\030\002 \001(\r\"+\n\005Snake\022\"\n\004body\030"
  "\001 \003(\0132\024.gameInfoProto.IVec2\"\360\001\n\010GameInfo"
  "\022\"\n\004food\030\001 \001(\0132\024.gameInfoProto.IVec2\022\"\n\004"
  "play\030\002 \001(\0162\024.gameInfoProto.State\022#\n\005snak"
  "e\030\003 \001(\0132\024.gameInfoProto.Snake\022%\n\007snakeOp"
  "\030\004 \003(\0132\024.gameInfoProto.Snake\022\022\n\nsnakeSpe"
  "ed\030\005 \001(\002\022+\n\tdirection\030\006 \001(\0162\030.gameInfoPr"
  "oto.Direction\022\017\n\007quitted\030\007 \001(\010*0\n\005State\022"
  "\n\n\006S_PLAY\020\000\022\013\n\007S_PAUSE\020\001\022\016\n\nS_GAMEOVER\020\002"
  "*S\n\tDirection\022\013\n\007NO_MOVE\020\000\022\013\n\007MOVE_UP\020\001\022"
  "\016\n\nMOVE_RIGHT\020\002\022\r\n\tMOVE_DOWN\020\003\022\r\n\tMOVE_L"
  "EFT\020\004b\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_gameInfo_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_gameInfo_2eproto_sccs[3] = {
  &scc_info_GameInfo_gameInfo_2eproto.base,
  &scc_info_IVec2_gameInfo_2eproto.base,
  &scc_info_Snake_gameInfo_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_gameInfo_2eproto_once;
static bool descriptor_table_gameInfo_2eproto_initialized = false;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_gameInfo_2eproto = {
  &descriptor_table_gameInfo_2eproto_initialized, descriptor_table_protodef_gameInfo_2eproto, "gameInfo.proto", 493,
  &descriptor_table_gameInfo_2eproto_once, descriptor_table_gameInfo_2eproto_sccs, descriptor_table_gameInfo_2eproto_deps, 3, 0,
  schemas, file_default_instances, TableStruct_gameInfo_2eproto::offsets,
  file_level_metadata_gameInfo_2eproto, 3, file_level_enum_descriptors_gameInfo_2eproto, file_level_service_descriptors_gameInfo_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_gameInfo_2eproto = (static_cast<void>(::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_gameInfo_2eproto)), true);
namespace gameInfoProto {
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* State_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_gameInfo_2eproto);
  return file_level_enum_descriptors_gameInfo_2eproto[0];
}
bool State_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
      return true;
    default:
      return false;
  }
}

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* Direction_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_gameInfo_2eproto);
  return file_level_enum_descriptors_gameInfo_2eproto[1];
}
bool Direction_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
      return true;
    default:
      return false;
  }
}


// ===================================================================

void IVec2::InitAsDefaultInstance() {
}
class IVec2::_Internal {
 public:
};

IVec2::IVec2()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:gameInfoProto.IVec2)
}
IVec2::IVec2(const IVec2& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&x_, &from.x_,
    static_cast<size_t>(reinterpret_cast<char*>(&y_) -
    reinterpret_cast<char*>(&x_)) + sizeof(y_));
  // @@protoc_insertion_point(copy_constructor:gameInfoProto.IVec2)
}

void IVec2::SharedCtor() {
  ::memset(&x_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&y_) -
      reinterpret_cast<char*>(&x_)) + sizeof(y_));
}

IVec2::~IVec2() {
  // @@protoc_insertion_point(destructor:gameInfoProto.IVec2)
  SharedDtor();
}

void IVec2::SharedDtor() {
}

void IVec2::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const IVec2& IVec2::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_IVec2_gameInfo_2eproto.base);
  return *internal_default_instance();
}


void IVec2::Clear() {
// @@protoc_insertion_point(message_clear_start:gameInfoProto.IVec2)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&x_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&y_) -
      reinterpret_cast<char*>(&x_)) + sizeof(y_));
  _internal_metadata_.Clear();
}

const char* IVec2::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // uint32 x = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          x_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // uint32 y = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          y_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* IVec2::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:gameInfoProto.IVec2)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // uint32 x = 1;
  if (this->x() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(1, this->_internal_x(), target);
  }

  // uint32 y = 2;
  if (this->y() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(2, this->_internal_y(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:gameInfoProto.IVec2)
  return target;
}

size_t IVec2::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:gameInfoProto.IVec2)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // uint32 x = 1;
  if (this->x() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
        this->_internal_x());
  }

  // uint32 y = 2;
  if (this->y() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
        this->_internal_y());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void IVec2::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:gameInfoProto.IVec2)
  GOOGLE_DCHECK_NE(&from, this);
  const IVec2* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<IVec2>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:gameInfoProto.IVec2)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:gameInfoProto.IVec2)
    MergeFrom(*source);
  }
}

void IVec2::MergeFrom(const IVec2& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:gameInfoProto.IVec2)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.x() != 0) {
    _internal_set_x(from._internal_x());
  }
  if (from.y() != 0) {
    _internal_set_y(from._internal_y());
  }
}

void IVec2::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:gameInfoProto.IVec2)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void IVec2::CopyFrom(const IVec2& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:gameInfoProto.IVec2)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool IVec2::IsInitialized() const {
  return true;
}

void IVec2::InternalSwap(IVec2* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(x_, other->x_);
  swap(y_, other->y_);
}

::PROTOBUF_NAMESPACE_ID::Metadata IVec2::GetMetadata() const {
  return GetMetadataStatic();
}


// ===================================================================

void Snake::InitAsDefaultInstance() {
}
class Snake::_Internal {
 public:
};

Snake::Snake()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:gameInfoProto.Snake)
}
Snake::Snake(const Snake& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr),
      body_(from.body_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:gameInfoProto.Snake)
}

void Snake::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_Snake_gameInfo_2eproto.base);
}

Snake::~Snake() {
  // @@protoc_insertion_point(destructor:gameInfoProto.Snake)
  SharedDtor();
}

void Snake::SharedDtor() {
}

void Snake::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const Snake& Snake::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_Snake_gameInfo_2eproto.base);
  return *internal_default_instance();
}


void Snake::Clear() {
// @@protoc_insertion_point(message_clear_start:gameInfoProto.Snake)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  body_.Clear();
  _internal_metadata_.Clear();
}

const char* Snake::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // repeated .gameInfoProto.IVec2 body = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_body(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<10>(ptr));
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* Snake::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:gameInfoProto.Snake)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .gameInfoProto.IVec2 body = 1;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->_internal_body_size()); i < n; i++) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(1, this->_internal_body(i), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:gameInfoProto.Snake)
  return target;
}

size_t Snake::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:gameInfoProto.Snake)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .gameInfoProto.IVec2 body = 1;
  total_size += 1UL * this->_internal_body_size();
  for (const auto& msg : this->body_) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void Snake::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:gameInfoProto.Snake)
  GOOGLE_DCHECK_NE(&from, this);
  const Snake* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<Snake>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:gameInfoProto.Snake)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:gameInfoProto.Snake)
    MergeFrom(*source);
  }
}

void Snake::MergeFrom(const Snake& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:gameInfoProto.Snake)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  body_.MergeFrom(from.body_);
}

void Snake::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:gameInfoProto.Snake)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Snake::CopyFrom(const Snake& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:gameInfoProto.Snake)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Snake::IsInitialized() const {
  return true;
}

void Snake::InternalSwap(Snake* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  body_.InternalSwap(&other->body_);
}

::PROTOBUF_NAMESPACE_ID::Metadata Snake::GetMetadata() const {
  return GetMetadataStatic();
}


// ===================================================================

void GameInfo::InitAsDefaultInstance() {
  ::gameInfoProto::_GameInfo_default_instance_._instance.get_mutable()->food_ = const_cast< ::gameInfoProto::IVec2*>(
      ::gameInfoProto::IVec2::internal_default_instance());
  ::gameInfoProto::_GameInfo_default_instance_._instance.get_mutable()->snake_ = const_cast< ::gameInfoProto::Snake*>(
      ::gameInfoProto::Snake::internal_default_instance());
}
class GameInfo::_Internal {
 public:
  static const ::gameInfoProto::IVec2& food(const GameInfo* msg);
  static const ::gameInfoProto::Snake& snake(const GameInfo* msg);
};

const ::gameInfoProto::IVec2&
GameInfo::_Internal::food(const GameInfo* msg) {
  return *msg->food_;
}
const ::gameInfoProto::Snake&
GameInfo::_Internal::snake(const GameInfo* msg) {
  return *msg->snake_;
}
GameInfo::GameInfo()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:gameInfoProto.GameInfo)
}
GameInfo::GameInfo(const GameInfo& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr),
      snakeop_(from.snakeop_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  if (from._internal_has_food()) {
    food_ = new ::gameInfoProto::IVec2(*from.food_);
  } else {
    food_ = nullptr;
  }
  if (from._internal_has_snake()) {
    snake_ = new ::gameInfoProto::Snake(*from.snake_);
  } else {
    snake_ = nullptr;
  }
  ::memcpy(&play_, &from.play_,
    static_cast<size_t>(reinterpret_cast<char*>(&quitted_) -
    reinterpret_cast<char*>(&play_)) + sizeof(quitted_));
  // @@protoc_insertion_point(copy_constructor:gameInfoProto.GameInfo)
}

void GameInfo::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_GameInfo_gameInfo_2eproto.base);
  ::memset(&food_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&quitted_) -
      reinterpret_cast<char*>(&food_)) + sizeof(quitted_));
}

GameInfo::~GameInfo() {
  // @@protoc_insertion_point(destructor:gameInfoProto.GameInfo)
  SharedDtor();
}

void GameInfo::SharedDtor() {
  if (this != internal_default_instance()) delete food_;
  if (this != internal_default_instance()) delete snake_;
}

void GameInfo::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const GameInfo& GameInfo::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_GameInfo_gameInfo_2eproto.base);
  return *internal_default_instance();
}


void GameInfo::Clear() {
// @@protoc_insertion_point(message_clear_start:gameInfoProto.GameInfo)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  snakeop_.Clear();
  if (GetArenaNoVirtual() == nullptr && food_ != nullptr) {
    delete food_;
  }
  food_ = nullptr;
  if (GetArenaNoVirtual() == nullptr && snake_ != nullptr) {
    delete snake_;
  }
  snake_ = nullptr;
  ::memset(&play_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&quitted_) -
      reinterpret_cast<char*>(&play_)) + sizeof(quitted_));
  _internal_metadata_.Clear();
}

const char* GameInfo::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // .gameInfoProto.IVec2 food = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr = ctx->ParseMessage(_internal_mutable_food(), ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // .gameInfoProto.State play = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_play(static_cast<::gameInfoProto::State>(val));
        } else goto handle_unusual;
        continue;
      // .gameInfoProto.Snake snake = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 26)) {
          ptr = ctx->ParseMessage(_internal_mutable_snake(), ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // repeated .gameInfoProto.Snake snakeOp = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 34)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_snakeop(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<34>(ptr));
        } else goto handle_unusual;
        continue;
      // float snakeSpeed = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 45)) {
          snakespeed_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else goto handle_unusual;
        continue;
      // .gameInfoProto.Direction direction = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 48)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_direction(static_cast<::gameInfoProto::Direction>(val));
        } else goto handle_unusual;
        continue;
      // bool quitted = 7;
      case 7:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 56)) {
          quitted_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* GameInfo::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:gameInfoProto.GameInfo)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .gameInfoProto.IVec2 food = 1;
  if (this->has_food()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        1, _Internal::food(this), target, stream);
  }

  // .gameInfoProto.State play = 2;
  if (this->play() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      2, this->_internal_play(), target);
  }

  // .gameInfoProto.Snake snake = 3;
  if (this->has_snake()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        3, _Internal::snake(this), target, stream);
  }

  // repeated .gameInfoProto.Snake snakeOp = 4;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->_internal_snakeop_size()); i < n; i++) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(4, this->_internal_snakeop(i), target, stream);
  }

  // float snakeSpeed = 5;
  if (!(this->snakespeed() <= 0 && this->snakespeed() >= 0)) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteFloatToArray(5, this->_internal_snakespeed(), target);
  }

  // .gameInfoProto.Direction direction = 6;
  if (this->direction() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      6, this->_internal_direction(), target);
  }

  // bool quitted = 7;
  if (this->quitted() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteBoolToArray(7, this->_internal_quitted(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:gameInfoProto.GameInfo)
  return target;
}

size_t GameInfo::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:gameInfoProto.GameInfo)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .gameInfoProto.Snake snakeOp = 4;
  total_size += 1UL * this->_internal_snakeop_size();
  for (const auto& msg : this->snakeop_) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  // .gameInfoProto.IVec2 food = 1;
  if (this->has_food()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *food_);
  }

  // .gameInfoProto.Snake snake = 3;
  if (this->has_snake()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *snake_);
  }

  // .gameInfoProto.State play = 2;
  if (this->play() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_play());
  }

  // float snakeSpeed = 5;
  if (!(this->snakespeed() <= 0 && this->snakespeed() >= 0)) {
    total_size += 1 + 4;
  }

  // .gameInfoProto.Direction direction = 6;
  if (this->direction() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_direction());
  }

  // bool quitted = 7;
  if (this->quitted() != 0) {
    total_size += 1 + 1;
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void GameInfo::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:gameInfoProto.GameInfo)
  GOOGLE_DCHECK_NE(&from, this);
  const GameInfo* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<GameInfo>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:gameInfoProto.GameInfo)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:gameInfoProto.GameInfo)
    MergeFrom(*source);
  }
}

void GameInfo::MergeFrom(const GameInfo& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:gameInfoProto.GameInfo)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  snakeop_.MergeFrom(from.snakeop_);
  if (from.has_food()) {
    _internal_mutable_food()->::gameInfoProto::IVec2::MergeFrom(from._internal_food());
  }
  if (from.has_snake()) {
    _internal_mutable_snake()->::gameInfoProto::Snake::MergeFrom(from._internal_snake());
  }
  if (from.play() != 0) {
    _internal_set_play(from._internal_play());
  }
  if (!(from.snakespeed() <= 0 && from.snakespeed() >= 0)) {
    _internal_set_snakespeed(from._internal_snakespeed());
  }
  if (from.direction() != 0) {
    _internal_set_direction(from._internal_direction());
  }
  if (from.quitted() != 0) {
    _internal_set_quitted(from._internal_quitted());
  }
}

void GameInfo::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:gameInfoProto.GameInfo)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void GameInfo::CopyFrom(const GameInfo& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:gameInfoProto.GameInfo)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool GameInfo::IsInitialized() const {
  return true;
}

void GameInfo::InternalSwap(GameInfo* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  snakeop_.InternalSwap(&other->snakeop_);
  swap(food_, other->food_);
  swap(snake_, other->snake_);
  swap(play_, other->play_);
  swap(snakespeed_, other->snakespeed_);
  swap(direction_, other->direction_);
  swap(quitted_, other->quitted_);
}

::PROTOBUF_NAMESPACE_ID::Metadata GameInfo::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace gameInfoProto
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::gameInfoProto::IVec2* Arena::CreateMaybeMessage< ::gameInfoProto::IVec2 >(Arena* arena) {
  return Arena::CreateInternal< ::gameInfoProto::IVec2 >(arena);
}
template<> PROTOBUF_NOINLINE ::gameInfoProto::Snake* Arena::CreateMaybeMessage< ::gameInfoProto::Snake >(Arena* arena) {
  return Arena::CreateInternal< ::gameInfoProto::Snake >(arena);
}
template<> PROTOBUF_NOINLINE ::gameInfoProto::GameInfo* Arena::CreateMaybeMessage< ::gameInfoProto::GameInfo >(Arena* arena) {
  return Arena::CreateInternal< ::gameInfoProto::GameInfo >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
