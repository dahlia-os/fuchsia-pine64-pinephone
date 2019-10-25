// WARNING: This file is machine generated by fidlgen.

#pragma once

#include <lib/fidl/internal.h>
#include <lib/fidl/txn_header.h>
#include <lib/fidl/llcpp/array.h>
#include <lib/fidl/llcpp/coding.h>
#include <lib/fidl/llcpp/connect_service.h>
#include <lib/fidl/llcpp/service_handler_interface.h>
#include <lib/fidl/llcpp/string_view.h>
#include <lib/fidl/llcpp/sync_call.h>
#include <lib/fidl/llcpp/traits.h>
#include <lib/fidl/llcpp/transaction.h>
#include <lib/fidl/llcpp/vector_view.h>
#include <lib/fit/function.h>
#include <lib/zx/channel.h>
#include <zircon/fidl.h>

namespace llcpp {

namespace fuchsia {
namespace buttons {

struct Buttons_RegisterNotify_Response;
struct Buttons_RegisterNotify_Result;
enum class ButtonType : uint8_t {
  VOLUME_UP = 0u,
  VOLUME_DOWN = 1u,
  RESET = 2u,
  MUTE = 3u,
  MAX = 4u,
};


class Buttons;



struct Buttons_RegisterNotify_Response {
  static constexpr const fidl_type_t* Type = nullptr;
  static constexpr uint32_t MaxNumHandles = 0;
  static constexpr uint32_t PrimarySize = 1;
  [[maybe_unused]]
  static constexpr uint32_t MaxOutOfLine = 0;

  uint8_t __reserved = {};
};

extern "C" const fidl_type_t fuchsia_buttons_Buttons_RegisterNotify_ResultTable;

struct Buttons_RegisterNotify_Result {
  enum class Tag : fidl_union_tag_t {
    kResponse = 0,
    kErr = 1,
    Invalid = ::std::numeric_limits<::fidl_union_tag_t>::max(),
  };

  Buttons_RegisterNotify_Result();
  ~Buttons_RegisterNotify_Result();

  Buttons_RegisterNotify_Result(Buttons_RegisterNotify_Result&& other) {
    tag_ = Tag::Invalid;
    if (this != &other) {
      MoveImpl_(std::move(other));
    }
  }

  Buttons_RegisterNotify_Result& operator=(Buttons_RegisterNotify_Result&& other) {
    if (this != &other) {
      MoveImpl_(std::move(other));
    }
    return *this;
  }

  bool has_invalid_tag() const { return tag_ == Tag::Invalid; }

  bool is_response() const { return tag_ == Tag::kResponse; }

  static Buttons_RegisterNotify_Result WithResponse(::llcpp::fuchsia::buttons::Buttons_RegisterNotify_Response&& val) {
    Buttons_RegisterNotify_Result result;
    result.set_response(std::move(val));
    return result;
  }

  ::llcpp::fuchsia::buttons::Buttons_RegisterNotify_Response& mutable_response();

  template <typename T>
  std::enable_if_t<std::is_convertible<T, ::llcpp::fuchsia::buttons::Buttons_RegisterNotify_Response>::value && std::is_copy_assignable<T>::value>
  set_response(const T& v) {
    mutable_response() = v;
  }

  template <typename T>
  std::enable_if_t<std::is_convertible<T, ::llcpp::fuchsia::buttons::Buttons_RegisterNotify_Response>::value && std::is_move_assignable<T>::value>
  set_response(T&& v) {
    mutable_response() = std::move(v);
  }

  ::llcpp::fuchsia::buttons::Buttons_RegisterNotify_Response const & response() const { return response_; }

  bool is_err() const { return tag_ == Tag::kErr; }

  static Buttons_RegisterNotify_Result WithErr(int32_t&& val) {
    Buttons_RegisterNotify_Result result;
    result.set_err(std::move(val));
    return result;
  }

  int32_t& mutable_err();

  template <typename T>
  std::enable_if_t<std::is_convertible<T, int32_t>::value && std::is_copy_assignable<T>::value>
  set_err(const T& v) {
    mutable_err() = v;
  }

  template <typename T>
  std::enable_if_t<std::is_convertible<T, int32_t>::value && std::is_move_assignable<T>::value>
  set_err(T&& v) {
    mutable_err() = std::move(v);
  }

  int32_t const & err() const { return err_; }

  Tag which() const { return tag_; }

  static constexpr const fidl_type_t* Type = &fuchsia_buttons_Buttons_RegisterNotify_ResultTable;
  static constexpr uint32_t MaxNumHandles = 0;
  static constexpr uint32_t PrimarySize = 8;
  [[maybe_unused]]
  static constexpr uint32_t MaxOutOfLine = 0;

 private:
  void Destroy();
  void MoveImpl_(Buttons_RegisterNotify_Result&& other);
  static void SizeAndOffsetAssertionHelper();
  Tag tag_;
  union {
    ::llcpp::fuchsia::buttons::Buttons_RegisterNotify_Response response_;
    int32_t err_;
  };
};

extern "C" const fidl_type_t fuchsia_buttons_ButtonsGetStateRequestTable;
extern "C" const fidl_type_t fuchsia_buttons_ButtonsGetStateResponseTable;
extern "C" const fidl_type_t fuchsia_buttons_ButtonsRegisterNotifyRequestTable;
extern "C" const fidl_type_t fuchsia_buttons_ButtonsRegisterNotifyResponseTable;
extern "C" const fidl_type_t fuchsia_buttons_ButtonsNotifyEventTable;

// Protocol for other devices to get the state of buttons and register for
// notifications of state change.
class Buttons final {
  Buttons() = delete;
 public:
  static constexpr char Name[] = "fuchsia.buttons.Buttons";

  struct GetStateResponse final {
    FIDL_ALIGNDECL
    fidl_message_header_t _hdr;
    bool pressed;

    static constexpr const fidl_type_t* Type = &fuchsia_buttons_ButtonsGetStateResponseTable;
    static constexpr uint32_t MaxNumHandles = 0;
    static constexpr uint32_t PrimarySize = 24;
    static constexpr uint32_t MaxOutOfLine = 0;
    static constexpr bool HasFlexibleEnvelope = false;
    static constexpr ::fidl::internal::TransactionalMessageKind MessageKind =
        ::fidl::internal::TransactionalMessageKind::kResponse;
  };
  struct GetStateRequest final {
    FIDL_ALIGNDECL
    fidl_message_header_t _hdr;
    ::llcpp::fuchsia::buttons::ButtonType type;

    static constexpr const fidl_type_t* Type = &fuchsia_buttons_ButtonsGetStateRequestTable;
    static constexpr uint32_t MaxNumHandles = 0;
    static constexpr uint32_t PrimarySize = 24;
    static constexpr uint32_t MaxOutOfLine = 0;
    static constexpr bool HasFlexibleEnvelope = false;
    static constexpr ::fidl::internal::TransactionalMessageKind MessageKind =
        ::fidl::internal::TransactionalMessageKind::kRequest;
    using ResponseType = GetStateResponse;
  };

  struct RegisterNotifyResponse final {
    FIDL_ALIGNDECL
    fidl_message_header_t _hdr;
    ::llcpp::fuchsia::buttons::Buttons_RegisterNotify_Result result;

    static constexpr const fidl_type_t* Type = &fuchsia_buttons_ButtonsRegisterNotifyResponseTable;
    static constexpr uint32_t MaxNumHandles = 0;
    static constexpr uint32_t PrimarySize = 24;
    static constexpr uint32_t MaxOutOfLine = 0;
    static constexpr bool HasFlexibleEnvelope = false;
    static constexpr ::fidl::internal::TransactionalMessageKind MessageKind =
        ::fidl::internal::TransactionalMessageKind::kResponse;
  };
  struct RegisterNotifyRequest final {
    FIDL_ALIGNDECL
    fidl_message_header_t _hdr;
    uint8_t types;

    static constexpr const fidl_type_t* Type = &fuchsia_buttons_ButtonsRegisterNotifyRequestTable;
    static constexpr uint32_t MaxNumHandles = 0;
    static constexpr uint32_t PrimarySize = 24;
    static constexpr uint32_t MaxOutOfLine = 0;
    static constexpr bool HasFlexibleEnvelope = false;
    static constexpr ::fidl::internal::TransactionalMessageKind MessageKind =
        ::fidl::internal::TransactionalMessageKind::kRequest;
    using ResponseType = RegisterNotifyResponse;
  };

  struct NotifyResponse final {
    FIDL_ALIGNDECL
    fidl_message_header_t _hdr;
    ::llcpp::fuchsia::buttons::ButtonType type;
    bool pressed;

    static constexpr const fidl_type_t* Type = &fuchsia_buttons_ButtonsNotifyEventTable;
    static constexpr uint32_t MaxNumHandles = 0;
    static constexpr uint32_t PrimarySize = 24;
    static constexpr uint32_t MaxOutOfLine = 0;
    static constexpr bool HasFlexibleEnvelope = false;
    static constexpr ::fidl::internal::TransactionalMessageKind MessageKind =
        ::fidl::internal::TransactionalMessageKind::kResponse;
  };

  struct EventHandlers {
    // Notify event. Called when state of previously registered button changes.
    // |type| : Button type.
    // |pressed| : True if button is pressed.
    fit::callback<zx_status_t(::llcpp::fuchsia::buttons::ButtonType type, bool pressed)> notify;

    // Fallback handler when an unknown ordinal is received.
    // Caller may put custom error handling logic here.
    fit::callback<zx_status_t()> unknown;
  };

  // Collection of return types of FIDL calls in this interface.
  class ResultOf final {
    ResultOf() = delete;
   private:
    template <typename ResponseType>
    class GetState_Impl final : private ::fidl::internal::OwnedSyncCallBase<ResponseType> {
      using Super = ::fidl::internal::OwnedSyncCallBase<ResponseType>;
     public:
      GetState_Impl(zx::unowned_channel _client_end, ::llcpp::fuchsia::buttons::ButtonType type);
      ~GetState_Impl() = default;
      GetState_Impl(GetState_Impl&& other) = default;
      GetState_Impl& operator=(GetState_Impl&& other) = default;
      using Super::status;
      using Super::error;
      using Super::ok;
      using Super::Unwrap;
      using Super::value;
      using Super::operator->;
      using Super::operator*;
    };
    template <typename ResponseType>
    class RegisterNotify_Impl final : private ::fidl::internal::OwnedSyncCallBase<ResponseType> {
      using Super = ::fidl::internal::OwnedSyncCallBase<ResponseType>;
     public:
      RegisterNotify_Impl(zx::unowned_channel _client_end, uint8_t types);
      ~RegisterNotify_Impl() = default;
      RegisterNotify_Impl(RegisterNotify_Impl&& other) = default;
      RegisterNotify_Impl& operator=(RegisterNotify_Impl&& other) = default;
      using Super::status;
      using Super::error;
      using Super::ok;
      using Super::Unwrap;
      using Super::value;
      using Super::operator->;
      using Super::operator*;
    };

   public:
    using GetState = GetState_Impl<GetStateResponse>;
    using RegisterNotify = RegisterNotify_Impl<RegisterNotifyResponse>;
  };

  // Collection of return types of FIDL calls in this interface,
  // when the caller-allocate flavor or in-place call is used.
  class UnownedResultOf final {
    UnownedResultOf() = delete;
   private:
    template <typename ResponseType>
    class GetState_Impl final : private ::fidl::internal::UnownedSyncCallBase<ResponseType> {
      using Super = ::fidl::internal::UnownedSyncCallBase<ResponseType>;
     public:
      GetState_Impl(zx::unowned_channel _client_end, ::fidl::BytePart _request_buffer, ::llcpp::fuchsia::buttons::ButtonType type, ::fidl::BytePart _response_buffer);
      ~GetState_Impl() = default;
      GetState_Impl(GetState_Impl&& other) = default;
      GetState_Impl& operator=(GetState_Impl&& other) = default;
      using Super::status;
      using Super::error;
      using Super::ok;
      using Super::Unwrap;
      using Super::value;
      using Super::operator->;
      using Super::operator*;
    };
    template <typename ResponseType>
    class RegisterNotify_Impl final : private ::fidl::internal::UnownedSyncCallBase<ResponseType> {
      using Super = ::fidl::internal::UnownedSyncCallBase<ResponseType>;
     public:
      RegisterNotify_Impl(zx::unowned_channel _client_end, ::fidl::BytePart _request_buffer, uint8_t types, ::fidl::BytePart _response_buffer);
      ~RegisterNotify_Impl() = default;
      RegisterNotify_Impl(RegisterNotify_Impl&& other) = default;
      RegisterNotify_Impl& operator=(RegisterNotify_Impl&& other) = default;
      using Super::status;
      using Super::error;
      using Super::ok;
      using Super::Unwrap;
      using Super::value;
      using Super::operator->;
      using Super::operator*;
    };

   public:
    using GetState = GetState_Impl<GetStateResponse>;
    using RegisterNotify = RegisterNotify_Impl<RegisterNotifyResponse>;
  };

  class SyncClient final {
   public:
    explicit SyncClient(::zx::channel channel) : channel_(std::move(channel)) {}
    ~SyncClient() = default;
    SyncClient(SyncClient&&) = default;
    SyncClient& operator=(SyncClient&&) = default;

    const ::zx::channel& channel() const { return channel_; }

    ::zx::channel* mutable_channel() { return &channel_; }

    // Gets the state of the button requested.
    // |type| : Button type.
    // @Returns: |pressed| : True if button is pressed.
    // Allocates 48 bytes of message buffer on the stack. No heap allocation necessary.
    ResultOf::GetState GetState(::llcpp::fuchsia::buttons::ButtonType type);

    // Gets the state of the button requested.
    // |type| : Button type.
    // @Returns: |pressed| : True if button is pressed.
    // Caller provides the backing storage for FIDL message via request and response buffers.
    UnownedResultOf::GetState GetState(::fidl::BytePart _request_buffer, ::llcpp::fuchsia::buttons::ButtonType type, ::fidl::BytePart _response_buffer);

    // Registers to receive notifications of a state change for some buttons.
    // |types| : Bitmask which indicates the interested buttons. 0 means not
    //           interested, 1 means interested. Bit position corresponds to
    //           ButtonType, e.g. (1 << VOLUME_UP) means notify only when
    //           the state of the VOLUME_UP button changes. Types not listed
    //           in subsequent calls are removed.
    // @Returns: |status| : ZX_OK if succeeds.
    // Allocates 48 bytes of message buffer on the stack. No heap allocation necessary.
    ResultOf::RegisterNotify RegisterNotify(uint8_t types);

    // Registers to receive notifications of a state change for some buttons.
    // |types| : Bitmask which indicates the interested buttons. 0 means not
    //           interested, 1 means interested. Bit position corresponds to
    //           ButtonType, e.g. (1 << VOLUME_UP) means notify only when
    //           the state of the VOLUME_UP button changes. Types not listed
    //           in subsequent calls are removed.
    // @Returns: |status| : ZX_OK if succeeds.
    // Caller provides the backing storage for FIDL message via request and response buffers.
    UnownedResultOf::RegisterNotify RegisterNotify(::fidl::BytePart _request_buffer, uint8_t types, ::fidl::BytePart _response_buffer);

    // Handle all possible events defined in this protocol.
    // Blocks to consume exactly one message from the channel, then call the corresponding handler
    // defined in |EventHandlers|. The return status of the handler function is folded with any
    // transport-level errors and returned.
    zx_status_t HandleEvents(EventHandlers handlers);
   private:
    ::zx::channel channel_;
  };

  // Methods to make a sync FIDL call directly on an unowned channel, avoiding setting up a client.
  class Call final {
    Call() = delete;
   public:

    // Gets the state of the button requested.
    // |type| : Button type.
    // @Returns: |pressed| : True if button is pressed.
    // Allocates 48 bytes of message buffer on the stack. No heap allocation necessary.
    static ResultOf::GetState GetState(zx::unowned_channel _client_end, ::llcpp::fuchsia::buttons::ButtonType type);

    // Gets the state of the button requested.
    // |type| : Button type.
    // @Returns: |pressed| : True if button is pressed.
    // Caller provides the backing storage for FIDL message via request and response buffers.
    static UnownedResultOf::GetState GetState(zx::unowned_channel _client_end, ::fidl::BytePart _request_buffer, ::llcpp::fuchsia::buttons::ButtonType type, ::fidl::BytePart _response_buffer);

    // Registers to receive notifications of a state change for some buttons.
    // |types| : Bitmask which indicates the interested buttons. 0 means not
    //           interested, 1 means interested. Bit position corresponds to
    //           ButtonType, e.g. (1 << VOLUME_UP) means notify only when
    //           the state of the VOLUME_UP button changes. Types not listed
    //           in subsequent calls are removed.
    // @Returns: |status| : ZX_OK if succeeds.
    // Allocates 48 bytes of message buffer on the stack. No heap allocation necessary.
    static ResultOf::RegisterNotify RegisterNotify(zx::unowned_channel _client_end, uint8_t types);

    // Registers to receive notifications of a state change for some buttons.
    // |types| : Bitmask which indicates the interested buttons. 0 means not
    //           interested, 1 means interested. Bit position corresponds to
    //           ButtonType, e.g. (1 << VOLUME_UP) means notify only when
    //           the state of the VOLUME_UP button changes. Types not listed
    //           in subsequent calls are removed.
    // @Returns: |status| : ZX_OK if succeeds.
    // Caller provides the backing storage for FIDL message via request and response buffers.
    static UnownedResultOf::RegisterNotify RegisterNotify(zx::unowned_channel _client_end, ::fidl::BytePart _request_buffer, uint8_t types, ::fidl::BytePart _response_buffer);

    // Handle all possible events defined in this protocol.
    // Blocks to consume exactly one message from the channel, then call the corresponding handler
    // defined in |EventHandlers|. The return status of the handler function is folded with any
    // transport-level errors and returned.
    static zx_status_t HandleEvents(zx::unowned_channel client_end, EventHandlers handlers);
  };

  // Messages are encoded and decoded in-place when these methods are used.
  // Additionally, requests must be already laid-out according to the FIDL wire-format.
  class InPlace final {
    InPlace() = delete;
   public:

    // Gets the state of the button requested.
    // |type| : Button type.
    // @Returns: |pressed| : True if button is pressed.
    static ::fidl::DecodeResult<GetStateResponse> GetState(zx::unowned_channel _client_end, ::fidl::DecodedMessage<GetStateRequest> params, ::fidl::BytePart response_buffer);

    // Registers to receive notifications of a state change for some buttons.
    // |types| : Bitmask which indicates the interested buttons. 0 means not
    //           interested, 1 means interested. Bit position corresponds to
    //           ButtonType, e.g. (1 << VOLUME_UP) means notify only when
    //           the state of the VOLUME_UP button changes. Types not listed
    //           in subsequent calls are removed.
    // @Returns: |status| : ZX_OK if succeeds.
    static ::fidl::DecodeResult<RegisterNotifyResponse> RegisterNotify(zx::unowned_channel _client_end, ::fidl::DecodedMessage<RegisterNotifyRequest> params, ::fidl::BytePart response_buffer);

  };

  // Pure-virtual interface to be implemented by a server.
  class Interface {
   public:
    Interface() = default;
    virtual ~Interface() = default;
    using _Outer = Buttons;
    using _Base = ::fidl::CompleterBase;

    class GetStateCompleterBase : public _Base {
     public:
      void Reply(bool pressed);
      void Reply(::fidl::BytePart _buffer, bool pressed);
      void Reply(::fidl::DecodedMessage<GetStateResponse> params);

     protected:
      using ::fidl::CompleterBase::CompleterBase;
    };

    using GetStateCompleter = ::fidl::Completer<GetStateCompleterBase>;

    virtual void GetState(::llcpp::fuchsia::buttons::ButtonType type, GetStateCompleter::Sync _completer) = 0;

    class RegisterNotifyCompleterBase : public _Base {
     public:
      void Reply(::llcpp::fuchsia::buttons::Buttons_RegisterNotify_Result result);
      void ReplySuccess();
      void ReplyError(int32_t error);
      void Reply(::fidl::BytePart _buffer, ::llcpp::fuchsia::buttons::Buttons_RegisterNotify_Result result);
      void ReplySuccess(::fidl::BytePart _buffer);
      void Reply(::fidl::DecodedMessage<RegisterNotifyResponse> params);

     protected:
      using ::fidl::CompleterBase::CompleterBase;
    };

    using RegisterNotifyCompleter = ::fidl::Completer<RegisterNotifyCompleterBase>;

    virtual void RegisterNotify(uint8_t types, RegisterNotifyCompleter::Sync _completer) = 0;

  };

  // Attempts to dispatch the incoming message to a handler function in the server implementation.
  // If there is no matching handler, it returns false, leaving the message and transaction intact.
  // In all other cases, it consumes the message and returns true.
  // It is possible to chain multiple TryDispatch functions in this manner.
  static bool TryDispatch(Interface* impl, fidl_msg_t* msg, ::fidl::Transaction* txn);

  // Dispatches the incoming message to one of the handlers functions in the interface.
  // If there is no matching handler, it closes all the handles in |msg| and closes the channel with
  // a |ZX_ERR_NOT_SUPPORTED| epitaph, before returning false. The message should then be discarded.
  static bool Dispatch(Interface* impl, fidl_msg_t* msg, ::fidl::Transaction* txn);

  // Same as |Dispatch|, but takes a |void*| instead of |Interface*|. Only used with |fidl::Bind|
  // to reduce template expansion.
  // Do not call this method manually. Use |Dispatch| instead.
  static bool TypeErasedDispatch(void* impl, fidl_msg_t* msg, ::fidl::Transaction* txn) {
    return Dispatch(static_cast<Interface*>(impl), msg, txn);
  }

  // Notify event. Called when state of previously registered button changes.
  // |type| : Button type.
  // |pressed| : True if button is pressed.
  static zx_status_t SendNotifyEvent(::zx::unowned_channel _chan, ::llcpp::fuchsia::buttons::ButtonType type, bool pressed);

  // Notify event. Called when state of previously registered button changes.
  // |type| : Button type.
  // |pressed| : True if button is pressed.
  // Caller provides the backing storage for FIDL message via response buffers.
  static zx_status_t SendNotifyEvent(::zx::unowned_channel _chan, ::fidl::BytePart _buffer, ::llcpp::fuchsia::buttons::ButtonType type, bool pressed);

  // Notify event. Called when state of previously registered button changes.
  // |type| : Button type.
  // |pressed| : True if button is pressed.
  // Messages are encoded in-place.
  static zx_status_t SendNotifyEvent(::zx::unowned_channel _chan, ::fidl::DecodedMessage<NotifyResponse> params);


  // Helper functions to fill in the transaction header in a |DecodedMessage<TransactionalMessage>|.
  class SetTransactionHeaderFor final {
    SetTransactionHeaderFor() = delete;
   public:
    static void GetStateRequest(const ::fidl::DecodedMessage<Buttons::GetStateRequest>& _msg);
    static void GetStateResponse(const ::fidl::DecodedMessage<Buttons::GetStateResponse>& _msg);
    static void RegisterNotifyRequest(const ::fidl::DecodedMessage<Buttons::RegisterNotifyRequest>& _msg);
    static void RegisterNotifyResponse(const ::fidl::DecodedMessage<Buttons::RegisterNotifyResponse>& _msg);
    static void NotifyResponse(const ::fidl::DecodedMessage<Buttons::NotifyResponse>& _msg);
  };
};

}  // namespace buttons
}  // namespace fuchsia
}  // namespace llcpp

namespace fidl {

template <>
struct IsFidlType<::llcpp::fuchsia::buttons::Buttons_RegisterNotify_Response> : public std::true_type {};
static_assert(std::is_standard_layout_v<::llcpp::fuchsia::buttons::Buttons_RegisterNotify_Response>);
static_assert(offsetof(::llcpp::fuchsia::buttons::Buttons_RegisterNotify_Response, __reserved) == 0);
static_assert(sizeof(::llcpp::fuchsia::buttons::Buttons_RegisterNotify_Response) == ::llcpp::fuchsia::buttons::Buttons_RegisterNotify_Response::PrimarySize);

template <>
struct IsFidlType<::llcpp::fuchsia::buttons::Buttons_RegisterNotify_Result> : public std::true_type {};
static_assert(std::is_standard_layout_v<::llcpp::fuchsia::buttons::Buttons_RegisterNotify_Result>);

template <>
struct IsFidlType<::llcpp::fuchsia::buttons::Buttons::GetStateRequest> : public std::true_type {};
template <>
struct IsFidlMessage<::llcpp::fuchsia::buttons::Buttons::GetStateRequest> : public std::true_type {};
static_assert(sizeof(::llcpp::fuchsia::buttons::Buttons::GetStateRequest)
    == ::llcpp::fuchsia::buttons::Buttons::GetStateRequest::PrimarySize);
static_assert(offsetof(::llcpp::fuchsia::buttons::Buttons::GetStateRequest, type) == 16);

template <>
struct IsFidlType<::llcpp::fuchsia::buttons::Buttons::GetStateResponse> : public std::true_type {};
template <>
struct IsFidlMessage<::llcpp::fuchsia::buttons::Buttons::GetStateResponse> : public std::true_type {};
static_assert(sizeof(::llcpp::fuchsia::buttons::Buttons::GetStateResponse)
    == ::llcpp::fuchsia::buttons::Buttons::GetStateResponse::PrimarySize);
static_assert(offsetof(::llcpp::fuchsia::buttons::Buttons::GetStateResponse, pressed) == 16);

template <>
struct IsFidlType<::llcpp::fuchsia::buttons::Buttons::RegisterNotifyRequest> : public std::true_type {};
template <>
struct IsFidlMessage<::llcpp::fuchsia::buttons::Buttons::RegisterNotifyRequest> : public std::true_type {};
static_assert(sizeof(::llcpp::fuchsia::buttons::Buttons::RegisterNotifyRequest)
    == ::llcpp::fuchsia::buttons::Buttons::RegisterNotifyRequest::PrimarySize);
static_assert(offsetof(::llcpp::fuchsia::buttons::Buttons::RegisterNotifyRequest, types) == 16);

template <>
struct IsFidlType<::llcpp::fuchsia::buttons::Buttons::RegisterNotifyResponse> : public std::true_type {};
template <>
struct IsFidlMessage<::llcpp::fuchsia::buttons::Buttons::RegisterNotifyResponse> : public std::true_type {};
static_assert(sizeof(::llcpp::fuchsia::buttons::Buttons::RegisterNotifyResponse)
    == ::llcpp::fuchsia::buttons::Buttons::RegisterNotifyResponse::PrimarySize);
static_assert(offsetof(::llcpp::fuchsia::buttons::Buttons::RegisterNotifyResponse, result) == 16);

template <>
struct IsFidlType<::llcpp::fuchsia::buttons::Buttons::NotifyResponse> : public std::true_type {};
template <>
struct IsFidlMessage<::llcpp::fuchsia::buttons::Buttons::NotifyResponse> : public std::true_type {};
static_assert(sizeof(::llcpp::fuchsia::buttons::Buttons::NotifyResponse)
    == ::llcpp::fuchsia::buttons::Buttons::NotifyResponse::PrimarySize);
static_assert(offsetof(::llcpp::fuchsia::buttons::Buttons::NotifyResponse, type) == 16);
static_assert(offsetof(::llcpp::fuchsia::buttons::Buttons::NotifyResponse, pressed) == 17);

}  // namespace fidl
