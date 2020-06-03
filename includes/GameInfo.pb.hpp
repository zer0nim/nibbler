// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: gameInfo.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_gameInfo_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_gameInfo_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3012000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3012003 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_gameInfo_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_gameInfo_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[3]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_gameInfo_2eproto;
namespace gameInfoProto {
class GameInfo;
class GameInfoDefaultTypeInternal;
extern GameInfoDefaultTypeInternal _GameInfo_default_instance_;
class IVec2;
class IVec2DefaultTypeInternal;
extern IVec2DefaultTypeInternal _IVec2_default_instance_;
class Snake;
class SnakeDefaultTypeInternal;
extern SnakeDefaultTypeInternal _Snake_default_instance_;
}  // namespace gameInfoProto
PROTOBUF_NAMESPACE_OPEN
template<> ::gameInfoProto::GameInfo* Arena::CreateMaybeMessage<::gameInfoProto::GameInfo>(Arena*);
template<> ::gameInfoProto::IVec2* Arena::CreateMaybeMessage<::gameInfoProto::IVec2>(Arena*);
template<> ::gameInfoProto::Snake* Arena::CreateMaybeMessage<::gameInfoProto::Snake>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace gameInfoProto {

enum State : int {
  S_PLAY = 0,
  S_PAUSE = 1,
  S_GAMEOVER = 2,
  State_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  State_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool State_IsValid(int value);
constexpr State State_MIN = S_PLAY;
constexpr State State_MAX = S_GAMEOVER;
constexpr int State_ARRAYSIZE = State_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* State_descriptor();
template<typename T>
inline const std::string& State_Name(T enum_t_value) {
  static_assert(::std::is_same<T, State>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function State_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    State_descriptor(), enum_t_value);
}
inline bool State_Parse(
    const std::string& name, State* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<State>(
    State_descriptor(), name, value);
}
enum Direction : int {
  NO_MOVE = 0,
  MOVE_UP = 1,
  MOVE_RIGHT = 2,
  MOVE_DOWN = 3,
  MOVE_LEFT = 4,
  Direction_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  Direction_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool Direction_IsValid(int value);
constexpr Direction Direction_MIN = NO_MOVE;
constexpr Direction Direction_MAX = MOVE_LEFT;
constexpr int Direction_ARRAYSIZE = Direction_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* Direction_descriptor();
template<typename T>
inline const std::string& Direction_Name(T enum_t_value) {
  static_assert(::std::is_same<T, Direction>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function Direction_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    Direction_descriptor(), enum_t_value);
}
inline bool Direction_Parse(
    const std::string& name, Direction* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<Direction>(
    Direction_descriptor(), name, value);
}
// ===================================================================

class IVec2 PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:gameInfoProto.IVec2) */ {
 public:
  inline IVec2() : IVec2(nullptr) {};
  virtual ~IVec2();

  IVec2(const IVec2& from);
  IVec2(IVec2&& from) noexcept
    : IVec2() {
    *this = ::std::move(from);
  }

  inline IVec2& operator=(const IVec2& from) {
    CopyFrom(from);
    return *this;
  }
  inline IVec2& operator=(IVec2&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const IVec2& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const IVec2* internal_default_instance() {
    return reinterpret_cast<const IVec2*>(
               &_IVec2_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(IVec2& a, IVec2& b) {
    a.Swap(&b);
  }
  inline void Swap(IVec2* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(IVec2* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline IVec2* New() const final {
    return CreateMaybeMessage<IVec2>(nullptr);
  }

  IVec2* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<IVec2>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const IVec2& from);
  void MergeFrom(const IVec2& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(IVec2* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "gameInfoProto.IVec2";
  }
  protected:
  explicit IVec2(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_gameInfo_2eproto);
    return ::descriptor_table_gameInfo_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kXFieldNumber = 1,
    kYFieldNumber = 2,
  };
  // uint32 x = 1;
  void clear_x();
  ::PROTOBUF_NAMESPACE_ID::uint32 x() const;
  void set_x(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_x() const;
  void _internal_set_x(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // uint32 y = 2;
  void clear_y();
  ::PROTOBUF_NAMESPACE_ID::uint32 y() const;
  void set_y(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_y() const;
  void _internal_set_y(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // @@protoc_insertion_point(class_scope:gameInfoProto.IVec2)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::uint32 x_;
  ::PROTOBUF_NAMESPACE_ID::uint32 y_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_gameInfo_2eproto;
};
// -------------------------------------------------------------------

class Snake PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:gameInfoProto.Snake) */ {
 public:
  inline Snake() : Snake(nullptr) {};
  virtual ~Snake();

  Snake(const Snake& from);
  Snake(Snake&& from) noexcept
    : Snake() {
    *this = ::std::move(from);
  }

  inline Snake& operator=(const Snake& from) {
    CopyFrom(from);
    return *this;
  }
  inline Snake& operator=(Snake&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const Snake& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Snake* internal_default_instance() {
    return reinterpret_cast<const Snake*>(
               &_Snake_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(Snake& a, Snake& b) {
    a.Swap(&b);
  }
  inline void Swap(Snake* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Snake* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Snake* New() const final {
    return CreateMaybeMessage<Snake>(nullptr);
  }

  Snake* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Snake>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Snake& from);
  void MergeFrom(const Snake& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Snake* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "gameInfoProto.Snake";
  }
  protected:
  explicit Snake(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_gameInfo_2eproto);
    return ::descriptor_table_gameInfo_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kBodyFieldNumber = 1,
  };
  // repeated .gameInfoProto.IVec2 body = 1;
  int body_size() const;
  private:
  int _internal_body_size() const;
  public:
  void clear_body();
  ::gameInfoProto::IVec2* mutable_body(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::gameInfoProto::IVec2 >*
      mutable_body();
  private:
  const ::gameInfoProto::IVec2& _internal_body(int index) const;
  ::gameInfoProto::IVec2* _internal_add_body();
  public:
  const ::gameInfoProto::IVec2& body(int index) const;
  ::gameInfoProto::IVec2* add_body();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::gameInfoProto::IVec2 >&
      body() const;

  // @@protoc_insertion_point(class_scope:gameInfoProto.Snake)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::gameInfoProto::IVec2 > body_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_gameInfo_2eproto;
};
// -------------------------------------------------------------------

class GameInfo PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:gameInfoProto.GameInfo) */ {
 public:
  inline GameInfo() : GameInfo(nullptr) {};
  virtual ~GameInfo();

  GameInfo(const GameInfo& from);
  GameInfo(GameInfo&& from) noexcept
    : GameInfo() {
    *this = ::std::move(from);
  }

  inline GameInfo& operator=(const GameInfo& from) {
    CopyFrom(from);
    return *this;
  }
  inline GameInfo& operator=(GameInfo&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const GameInfo& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const GameInfo* internal_default_instance() {
    return reinterpret_cast<const GameInfo*>(
               &_GameInfo_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  friend void swap(GameInfo& a, GameInfo& b) {
    a.Swap(&b);
  }
  inline void Swap(GameInfo* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(GameInfo* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline GameInfo* New() const final {
    return CreateMaybeMessage<GameInfo>(nullptr);
  }

  GameInfo* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<GameInfo>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const GameInfo& from);
  void MergeFrom(const GameInfo& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(GameInfo* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "gameInfoProto.GameInfo";
  }
  protected:
  explicit GameInfo(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_gameInfo_2eproto);
    return ::descriptor_table_gameInfo_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kSnakeOpFieldNumber = 4,
    kFoodFieldNumber = 1,
    kSnakeFieldNumber = 3,
    kPlayFieldNumber = 2,
    kSnakeSpeedFieldNumber = 5,
    kDirectionFieldNumber = 6,
    kQuittedFieldNumber = 7,
  };
  // repeated .gameInfoProto.Snake snakeOp = 4;
  int snakeop_size() const;
  private:
  int _internal_snakeop_size() const;
  public:
  void clear_snakeop();
  ::gameInfoProto::Snake* mutable_snakeop(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::gameInfoProto::Snake >*
      mutable_snakeop();
  private:
  const ::gameInfoProto::Snake& _internal_snakeop(int index) const;
  ::gameInfoProto::Snake* _internal_add_snakeop();
  public:
  const ::gameInfoProto::Snake& snakeop(int index) const;
  ::gameInfoProto::Snake* add_snakeop();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::gameInfoProto::Snake >&
      snakeop() const;

  // .gameInfoProto.IVec2 food = 1;
  bool has_food() const;
  private:
  bool _internal_has_food() const;
  public:
  void clear_food();
  const ::gameInfoProto::IVec2& food() const;
  ::gameInfoProto::IVec2* release_food();
  ::gameInfoProto::IVec2* mutable_food();
  void set_allocated_food(::gameInfoProto::IVec2* food);
  private:
  const ::gameInfoProto::IVec2& _internal_food() const;
  ::gameInfoProto::IVec2* _internal_mutable_food();
  public:
  void unsafe_arena_set_allocated_food(
      ::gameInfoProto::IVec2* food);
  ::gameInfoProto::IVec2* unsafe_arena_release_food();

  // .gameInfoProto.Snake snake = 3;
  bool has_snake() const;
  private:
  bool _internal_has_snake() const;
  public:
  void clear_snake();
  const ::gameInfoProto::Snake& snake() const;
  ::gameInfoProto::Snake* release_snake();
  ::gameInfoProto::Snake* mutable_snake();
  void set_allocated_snake(::gameInfoProto::Snake* snake);
  private:
  const ::gameInfoProto::Snake& _internal_snake() const;
  ::gameInfoProto::Snake* _internal_mutable_snake();
  public:
  void unsafe_arena_set_allocated_snake(
      ::gameInfoProto::Snake* snake);
  ::gameInfoProto::Snake* unsafe_arena_release_snake();

  // .gameInfoProto.State play = 2;
  void clear_play();
  ::gameInfoProto::State play() const;
  void set_play(::gameInfoProto::State value);
  private:
  ::gameInfoProto::State _internal_play() const;
  void _internal_set_play(::gameInfoProto::State value);
  public:

  // float snakeSpeed = 5;
  void clear_snakespeed();
  float snakespeed() const;
  void set_snakespeed(float value);
  private:
  float _internal_snakespeed() const;
  void _internal_set_snakespeed(float value);
  public:

  // .gameInfoProto.Direction direction = 6;
  void clear_direction();
  ::gameInfoProto::Direction direction() const;
  void set_direction(::gameInfoProto::Direction value);
  private:
  ::gameInfoProto::Direction _internal_direction() const;
  void _internal_set_direction(::gameInfoProto::Direction value);
  public:

  // bool quitted = 7;
  void clear_quitted();
  bool quitted() const;
  void set_quitted(bool value);
  private:
  bool _internal_quitted() const;
  void _internal_set_quitted(bool value);
  public:

  // @@protoc_insertion_point(class_scope:gameInfoProto.GameInfo)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::gameInfoProto::Snake > snakeop_;
  ::gameInfoProto::IVec2* food_;
  ::gameInfoProto::Snake* snake_;
  int play_;
  float snakespeed_;
  int direction_;
  bool quitted_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_gameInfo_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// IVec2

// uint32 x = 1;
inline void IVec2::clear_x() {
  x_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 IVec2::_internal_x() const {
  return x_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 IVec2::x() const {
  // @@protoc_insertion_point(field_get:gameInfoProto.IVec2.x)
  return _internal_x();
}
inline void IVec2::_internal_set_x(::PROTOBUF_NAMESPACE_ID::uint32 value) {

  x_ = value;
}
inline void IVec2::set_x(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_x(value);
  // @@protoc_insertion_point(field_set:gameInfoProto.IVec2.x)
}

// uint32 y = 2;
inline void IVec2::clear_y() {
  y_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 IVec2::_internal_y() const {
  return y_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 IVec2::y() const {
  // @@protoc_insertion_point(field_get:gameInfoProto.IVec2.y)
  return _internal_y();
}
inline void IVec2::_internal_set_y(::PROTOBUF_NAMESPACE_ID::uint32 value) {

  y_ = value;
}
inline void IVec2::set_y(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_y(value);
  // @@protoc_insertion_point(field_set:gameInfoProto.IVec2.y)
}

// -------------------------------------------------------------------

// Snake

// repeated .gameInfoProto.IVec2 body = 1;
inline int Snake::_internal_body_size() const {
  return body_.size();
}
inline int Snake::body_size() const {
  return _internal_body_size();
}
inline void Snake::clear_body() {
  body_.Clear();
}
inline ::gameInfoProto::IVec2* Snake::mutable_body(int index) {
  // @@protoc_insertion_point(field_mutable:gameInfoProto.Snake.body)
  return body_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::gameInfoProto::IVec2 >*
Snake::mutable_body() {
  // @@protoc_insertion_point(field_mutable_list:gameInfoProto.Snake.body)
  return &body_;
}
inline const ::gameInfoProto::IVec2& Snake::_internal_body(int index) const {
  return body_.Get(index);
}
inline const ::gameInfoProto::IVec2& Snake::body(int index) const {
  // @@protoc_insertion_point(field_get:gameInfoProto.Snake.body)
  return _internal_body(index);
}
inline ::gameInfoProto::IVec2* Snake::_internal_add_body() {
  return body_.Add();
}
inline ::gameInfoProto::IVec2* Snake::add_body() {
  // @@protoc_insertion_point(field_add:gameInfoProto.Snake.body)
  return _internal_add_body();
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::gameInfoProto::IVec2 >&
Snake::body() const {
  // @@protoc_insertion_point(field_list:gameInfoProto.Snake.body)
  return body_;
}

// -------------------------------------------------------------------

// GameInfo

// .gameInfoProto.IVec2 food = 1;
inline bool GameInfo::_internal_has_food() const {
  return this != internal_default_instance() && food_ != nullptr;
}
inline bool GameInfo::has_food() const {
  return _internal_has_food();
}
inline void GameInfo::clear_food() {
  if (GetArena() == nullptr && food_ != nullptr) {
    delete food_;
  }
  food_ = nullptr;
}
inline const ::gameInfoProto::IVec2& GameInfo::_internal_food() const {
  const ::gameInfoProto::IVec2* p = food_;
  return p != nullptr ? *p : *reinterpret_cast<const ::gameInfoProto::IVec2*>(
      &::gameInfoProto::_IVec2_default_instance_);
}
inline const ::gameInfoProto::IVec2& GameInfo::food() const {
  // @@protoc_insertion_point(field_get:gameInfoProto.GameInfo.food)
  return _internal_food();
}
inline void GameInfo::unsafe_arena_set_allocated_food(
    ::gameInfoProto::IVec2* food) {
  if (GetArena() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(food_);
  }
  food_ = food;
  if (food) {

  } else {

  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:gameInfoProto.GameInfo.food)
}
inline ::gameInfoProto::IVec2* GameInfo::release_food() {
  auto temp = unsafe_arena_release_food();
  if (GetArena() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
  return temp;
}
inline ::gameInfoProto::IVec2* GameInfo::unsafe_arena_release_food() {
  // @@protoc_insertion_point(field_release:gameInfoProto.GameInfo.food)

  ::gameInfoProto::IVec2* temp = food_;
  food_ = nullptr;
  return temp;
}
inline ::gameInfoProto::IVec2* GameInfo::_internal_mutable_food() {

  if (food_ == nullptr) {
    auto* p = CreateMaybeMessage<::gameInfoProto::IVec2>(GetArena());
    food_ = p;
  }
  return food_;
}
inline ::gameInfoProto::IVec2* GameInfo::mutable_food() {
  // @@protoc_insertion_point(field_mutable:gameInfoProto.GameInfo.food)
  return _internal_mutable_food();
}
inline void GameInfo::set_allocated_food(::gameInfoProto::IVec2* food) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArena();
  if (message_arena == nullptr) {
    delete food_;
  }
  if (food) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
      ::PROTOBUF_NAMESPACE_ID::Arena::GetArena(food);
    if (message_arena != submessage_arena) {
      food = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, food, submessage_arena);
    }

  } else {

  }
  food_ = food;
  // @@protoc_insertion_point(field_set_allocated:gameInfoProto.GameInfo.food)
}

// .gameInfoProto.State play = 2;
inline void GameInfo::clear_play() {
  play_ = 0;
}
inline ::gameInfoProto::State GameInfo::_internal_play() const {
  return static_cast< ::gameInfoProto::State >(play_);
}
inline ::gameInfoProto::State GameInfo::play() const {
  // @@protoc_insertion_point(field_get:gameInfoProto.GameInfo.play)
  return _internal_play();
}
inline void GameInfo::_internal_set_play(::gameInfoProto::State value) {

  play_ = value;
}
inline void GameInfo::set_play(::gameInfoProto::State value) {
  _internal_set_play(value);
  // @@protoc_insertion_point(field_set:gameInfoProto.GameInfo.play)
}

// .gameInfoProto.Snake snake = 3;
inline bool GameInfo::_internal_has_snake() const {
  return this != internal_default_instance() && snake_ != nullptr;
}
inline bool GameInfo::has_snake() const {
  return _internal_has_snake();
}
inline void GameInfo::clear_snake() {
  if (GetArena() == nullptr && snake_ != nullptr) {
    delete snake_;
  }
  snake_ = nullptr;
}
inline const ::gameInfoProto::Snake& GameInfo::_internal_snake() const {
  const ::gameInfoProto::Snake* p = snake_;
  return p != nullptr ? *p : *reinterpret_cast<const ::gameInfoProto::Snake*>(
      &::gameInfoProto::_Snake_default_instance_);
}
inline const ::gameInfoProto::Snake& GameInfo::snake() const {
  // @@protoc_insertion_point(field_get:gameInfoProto.GameInfo.snake)
  return _internal_snake();
}
inline void GameInfo::unsafe_arena_set_allocated_snake(
    ::gameInfoProto::Snake* snake) {
  if (GetArena() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(snake_);
  }
  snake_ = snake;
  if (snake) {

  } else {

  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:gameInfoProto.GameInfo.snake)
}
inline ::gameInfoProto::Snake* GameInfo::release_snake() {
  auto temp = unsafe_arena_release_snake();
  if (GetArena() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
  return temp;
}
inline ::gameInfoProto::Snake* GameInfo::unsafe_arena_release_snake() {
  // @@protoc_insertion_point(field_release:gameInfoProto.GameInfo.snake)

  ::gameInfoProto::Snake* temp = snake_;
  snake_ = nullptr;
  return temp;
}
inline ::gameInfoProto::Snake* GameInfo::_internal_mutable_snake() {

  if (snake_ == nullptr) {
    auto* p = CreateMaybeMessage<::gameInfoProto::Snake>(GetArena());
    snake_ = p;
  }
  return snake_;
}
inline ::gameInfoProto::Snake* GameInfo::mutable_snake() {
  // @@protoc_insertion_point(field_mutable:gameInfoProto.GameInfo.snake)
  return _internal_mutable_snake();
}
inline void GameInfo::set_allocated_snake(::gameInfoProto::Snake* snake) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArena();
  if (message_arena == nullptr) {
    delete snake_;
  }
  if (snake) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
      ::PROTOBUF_NAMESPACE_ID::Arena::GetArena(snake);
    if (message_arena != submessage_arena) {
      snake = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, snake, submessage_arena);
    }

  } else {

  }
  snake_ = snake;
  // @@protoc_insertion_point(field_set_allocated:gameInfoProto.GameInfo.snake)
}

// repeated .gameInfoProto.Snake snakeOp = 4;
inline int GameInfo::_internal_snakeop_size() const {
  return snakeop_.size();
}
inline int GameInfo::snakeop_size() const {
  return _internal_snakeop_size();
}
inline void GameInfo::clear_snakeop() {
  snakeop_.Clear();
}
inline ::gameInfoProto::Snake* GameInfo::mutable_snakeop(int index) {
  // @@protoc_insertion_point(field_mutable:gameInfoProto.GameInfo.snakeOp)
  return snakeop_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::gameInfoProto::Snake >*
GameInfo::mutable_snakeop() {
  // @@protoc_insertion_point(field_mutable_list:gameInfoProto.GameInfo.snakeOp)
  return &snakeop_;
}
inline const ::gameInfoProto::Snake& GameInfo::_internal_snakeop(int index) const {
  return snakeop_.Get(index);
}
inline const ::gameInfoProto::Snake& GameInfo::snakeop(int index) const {
  // @@protoc_insertion_point(field_get:gameInfoProto.GameInfo.snakeOp)
  return _internal_snakeop(index);
}
inline ::gameInfoProto::Snake* GameInfo::_internal_add_snakeop() {
  return snakeop_.Add();
}
inline ::gameInfoProto::Snake* GameInfo::add_snakeop() {
  // @@protoc_insertion_point(field_add:gameInfoProto.GameInfo.snakeOp)
  return _internal_add_snakeop();
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::gameInfoProto::Snake >&
GameInfo::snakeop() const {
  // @@protoc_insertion_point(field_list:gameInfoProto.GameInfo.snakeOp)
  return snakeop_;
}

// float snakeSpeed = 5;
inline void GameInfo::clear_snakespeed() {
  snakespeed_ = 0;
}
inline float GameInfo::_internal_snakespeed() const {
  return snakespeed_;
}
inline float GameInfo::snakespeed() const {
  // @@protoc_insertion_point(field_get:gameInfoProto.GameInfo.snakeSpeed)
  return _internal_snakespeed();
}
inline void GameInfo::_internal_set_snakespeed(float value) {

  snakespeed_ = value;
}
inline void GameInfo::set_snakespeed(float value) {
  _internal_set_snakespeed(value);
  // @@protoc_insertion_point(field_set:gameInfoProto.GameInfo.snakeSpeed)
}

// .gameInfoProto.Direction direction = 6;
inline void GameInfo::clear_direction() {
  direction_ = 0;
}
inline ::gameInfoProto::Direction GameInfo::_internal_direction() const {
  return static_cast< ::gameInfoProto::Direction >(direction_);
}
inline ::gameInfoProto::Direction GameInfo::direction() const {
  // @@protoc_insertion_point(field_get:gameInfoProto.GameInfo.direction)
  return _internal_direction();
}
inline void GameInfo::_internal_set_direction(::gameInfoProto::Direction value) {

  direction_ = value;
}
inline void GameInfo::set_direction(::gameInfoProto::Direction value) {
  _internal_set_direction(value);
  // @@protoc_insertion_point(field_set:gameInfoProto.GameInfo.direction)
}

// bool quitted = 7;
inline void GameInfo::clear_quitted() {
  quitted_ = false;
}
inline bool GameInfo::_internal_quitted() const {
  return quitted_;
}
inline bool GameInfo::quitted() const {
  // @@protoc_insertion_point(field_get:gameInfoProto.GameInfo.quitted)
  return _internal_quitted();
}
inline void GameInfo::_internal_set_quitted(bool value) {

  quitted_ = value;
}
inline void GameInfo::set_quitted(bool value) {
  _internal_set_quitted(value);
  // @@protoc_insertion_point(field_set:gameInfoProto.GameInfo.quitted)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace gameInfoProto

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::gameInfoProto::State> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::gameInfoProto::State>() {
  return ::gameInfoProto::State_descriptor();
}
template <> struct is_proto_enum< ::gameInfoProto::Direction> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::gameInfoProto::Direction>() {
  return ::gameInfoProto::Direction_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_gameInfo_2eproto
