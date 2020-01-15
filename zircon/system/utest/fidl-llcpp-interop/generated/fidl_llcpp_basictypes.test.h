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
#include <lib/zx/eventpair.h>
#include <zircon/fidl.h>

namespace llcpp {

namespace fidl {
namespace test {
namespace llcpp {
namespace basictypes {

struct SimpleStruct;
class TestInterface;

extern "C" const fidl_type_t v1_fidl_test_llcpp_basictypes_SimpleStructTable;

struct SimpleStruct {
  static constexpr const fidl_type_t* Type = &v1_fidl_test_llcpp_basictypes_SimpleStructTable;
  static constexpr uint32_t MaxNumHandles = 21;
  static constexpr uint32_t PrimarySize = 88;
  [[maybe_unused]]
  static constexpr uint32_t MaxOutOfLine = 0;
  static constexpr bool HasPointer = false;

  int32_t field = {};

  ::zx::eventpair ep = {};

  ::fidl::Array<::fidl::Array<::zx::eventpair, 4>, 5> arr = {};
};

extern "C" const fidl_type_t v1_fidl_test_llcpp_basictypes_TestInterfaceConsumeSimpleStructRequestTable;
extern "C" const fidl_type_t v1_fidl_test_llcpp_basictypes_TestInterfaceConsumeSimpleStructResponseTable;

// Test interface implemented by both C and LLCPP
class TestInterface final {
  TestInterface() = delete;
 public:

  struct ConsumeSimpleStructResponse final {
    FIDL_ALIGNDECL
    fidl_message_header_t _hdr;
    int32_t status;
    int32_t field;

    static constexpr const fidl_type_t* Type = &v1_fidl_test_llcpp_basictypes_TestInterfaceConsumeSimpleStructResponseTable;
    static constexpr uint32_t MaxNumHandles = 0;
    static constexpr uint32_t PrimarySize = 24;
    static constexpr uint32_t MaxOutOfLine = 0;
    static constexpr bool HasFlexibleEnvelope = false;
    static constexpr bool HasPointer = false;
    static constexpr bool ContainsUnion = false;
    static constexpr ::fidl::internal::TransactionalMessageKind MessageKind =
        ::fidl::internal::TransactionalMessageKind::kResponse;
  };
  struct ConsumeSimpleStructRequest final {
    FIDL_ALIGNDECL
    fidl_message_header_t _hdr;
    ::llcpp::fidl::test::llcpp::basictypes::SimpleStruct arg;

    static constexpr const fidl_type_t* Type = &v1_fidl_test_llcpp_basictypes_TestInterfaceConsumeSimpleStructRequestTable;
    static constexpr uint32_t MaxNumHandles = 21;
    static constexpr uint32_t PrimarySize = 104;
    static constexpr uint32_t MaxOutOfLine = 0;
    static constexpr uint32_t AltPrimarySize = 104;
    static constexpr uint32_t AltMaxOutOfLine = 0;
    static constexpr bool HasFlexibleEnvelope = false;
    static constexpr bool HasPointer = false;
    static constexpr bool ContainsUnion = false;
    static constexpr ::fidl::internal::TransactionalMessageKind MessageKind =
        ::fidl::internal::TransactionalMessageKind::kRequest;
    using ResponseType = ConsumeSimpleStructResponse;
  };


  // Collection of return types of FIDL calls in this interface.
  class ResultOf final {
    ResultOf() = delete;
   private:
    template <typename ResponseType>
    class ConsumeSimpleStruct_Impl final : private ::fidl::internal::OwnedSyncCallBase<ResponseType> {
      using Super = ::fidl::internal::OwnedSyncCallBase<ResponseType>;
     public:
      ConsumeSimpleStruct_Impl(::zx::unowned_channel _client_end, ::llcpp::fidl::test::llcpp::basictypes::SimpleStruct arg);
      ~ConsumeSimpleStruct_Impl() = default;
      ConsumeSimpleStruct_Impl(ConsumeSimpleStruct_Impl&& other) = default;
      ConsumeSimpleStruct_Impl& operator=(ConsumeSimpleStruct_Impl&& other) = default;
      using Super::status;
      using Super::error;
      using Super::ok;
      using Super::Unwrap;
      using Super::value;
      using Super::operator->;
      using Super::operator*;
    };

   public:
    using ConsumeSimpleStruct = ConsumeSimpleStruct_Impl<ConsumeSimpleStructResponse>;
  };

  // Collection of return types of FIDL calls in this interface,
  // when the caller-allocate flavor or in-place call is used.
  class UnownedResultOf final {
    UnownedResultOf() = delete;
   private:
    template <typename ResponseType>
    class ConsumeSimpleStruct_Impl final : private ::fidl::internal::UnownedSyncCallBase<ResponseType> {
      using Super = ::fidl::internal::UnownedSyncCallBase<ResponseType>;
     public:
      ConsumeSimpleStruct_Impl(::zx::unowned_channel _client_end, ::fidl::BytePart _request_buffer, ::llcpp::fidl::test::llcpp::basictypes::SimpleStruct arg, ::fidl::BytePart _response_buffer);
      ~ConsumeSimpleStruct_Impl() = default;
      ConsumeSimpleStruct_Impl(ConsumeSimpleStruct_Impl&& other) = default;
      ConsumeSimpleStruct_Impl& operator=(ConsumeSimpleStruct_Impl&& other) = default;
      using Super::status;
      using Super::error;
      using Super::ok;
      using Super::Unwrap;
      using Super::value;
      using Super::operator->;
      using Super::operator*;
    };

   public:
    using ConsumeSimpleStruct = ConsumeSimpleStruct_Impl<ConsumeSimpleStructResponse>;
  };

  class SyncClient final {
   public:
    explicit SyncClient(::zx::channel channel) : channel_(std::move(channel)) {}
    ~SyncClient() = default;
    SyncClient(SyncClient&&) = default;
    SyncClient& operator=(SyncClient&&) = default;

    const ::zx::channel& channel() const { return channel_; }

    ::zx::channel* mutable_channel() { return &channel_; }

    // Verifies that all the handles are valid channels, then returns
    // `ZX_OK` and loops back the field member. Otherwise, returns an error.
    // Allocates 128 bytes of message buffer on the stack. No heap allocation necessary.
    ResultOf::ConsumeSimpleStruct ConsumeSimpleStruct(::llcpp::fidl::test::llcpp::basictypes::SimpleStruct arg);

    // Verifies that all the handles are valid channels, then returns
    // `ZX_OK` and loops back the field member. Otherwise, returns an error.
    // Caller provides the backing storage for FIDL message via request and response buffers.
    UnownedResultOf::ConsumeSimpleStruct ConsumeSimpleStruct(::fidl::BytePart _request_buffer, ::llcpp::fidl::test::llcpp::basictypes::SimpleStruct arg, ::fidl::BytePart _response_buffer);

   private:
    ::zx::channel channel_;
  };

  // Methods to make a sync FIDL call directly on an unowned channel, avoiding setting up a client.
  class Call final {
    Call() = delete;
   public:

    // Verifies that all the handles are valid channels, then returns
    // `ZX_OK` and loops back the field member. Otherwise, returns an error.
    // Allocates 128 bytes of message buffer on the stack. No heap allocation necessary.
    static ResultOf::ConsumeSimpleStruct ConsumeSimpleStruct(::zx::unowned_channel _client_end, ::llcpp::fidl::test::llcpp::basictypes::SimpleStruct arg);

    // Verifies that all the handles are valid channels, then returns
    // `ZX_OK` and loops back the field member. Otherwise, returns an error.
    // Caller provides the backing storage for FIDL message via request and response buffers.
    static UnownedResultOf::ConsumeSimpleStruct ConsumeSimpleStruct(::zx::unowned_channel _client_end, ::fidl::BytePart _request_buffer, ::llcpp::fidl::test::llcpp::basictypes::SimpleStruct arg, ::fidl::BytePart _response_buffer);

  };

  // Messages are encoded and decoded in-place when these methods are used.
  // Additionally, requests must be already laid-out according to the FIDL wire-format.
  class InPlace final {
    InPlace() = delete;
   public:

    // Verifies that all the handles are valid channels, then returns
    // `ZX_OK` and loops back the field member. Otherwise, returns an error.
    static ::fidl::DecodeResult<ConsumeSimpleStructResponse> ConsumeSimpleStruct(::zx::unowned_channel _client_end, ::fidl::DecodedMessage<ConsumeSimpleStructRequest> params, ::fidl::BytePart response_buffer);

  };

  // Pure-virtual interface to be implemented by a server.
  class Interface {
   public:
    Interface() = default;
    virtual ~Interface() = default;
    using _Outer = TestInterface;
    using _Base = ::fidl::CompleterBase;

    class ConsumeSimpleStructCompleterBase : public _Base {
     public:
      void Reply(int32_t status, int32_t field);
      void Reply(::fidl::BytePart _buffer, int32_t status, int32_t field);
      void Reply(::fidl::DecodedMessage<ConsumeSimpleStructResponse> params);

     protected:
      using ::fidl::CompleterBase::CompleterBase;
    };

    using ConsumeSimpleStructCompleter = ::fidl::Completer<ConsumeSimpleStructCompleterBase>;

    virtual void ConsumeSimpleStruct(::llcpp::fidl::test::llcpp::basictypes::SimpleStruct arg, ConsumeSimpleStructCompleter::Sync _completer) = 0;

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


  // Helper functions to fill in the transaction header in a |DecodedMessage<TransactionalMessage>|.
  class SetTransactionHeaderFor final {
    SetTransactionHeaderFor() = delete;
   public:
    static void ConsumeSimpleStructRequest(const ::fidl::DecodedMessage<TestInterface::ConsumeSimpleStructRequest>& _msg);
    static void ConsumeSimpleStructResponse(const ::fidl::DecodedMessage<TestInterface::ConsumeSimpleStructResponse>& _msg);
  };
};

}  // namespace basictypes
}  // namespace llcpp
}  // namespace test
}  // namespace fidl
}  // namespace llcpp

namespace fidl {

template <>
struct IsFidlType<::llcpp::fidl::test::llcpp::basictypes::SimpleStruct> : public std::true_type {};
static_assert(std::is_standard_layout_v<::llcpp::fidl::test::llcpp::basictypes::SimpleStruct>);
static_assert(offsetof(::llcpp::fidl::test::llcpp::basictypes::SimpleStruct, field) == 0);
static_assert(offsetof(::llcpp::fidl::test::llcpp::basictypes::SimpleStruct, ep) == 4);
static_assert(offsetof(::llcpp::fidl::test::llcpp::basictypes::SimpleStruct, arr) == 8);
static_assert(sizeof(::llcpp::fidl::test::llcpp::basictypes::SimpleStruct) == ::llcpp::fidl::test::llcpp::basictypes::SimpleStruct::PrimarySize);

template <>
struct IsFidlType<::llcpp::fidl::test::llcpp::basictypes::TestInterface::ConsumeSimpleStructRequest> : public std::true_type {};
template <>
struct IsFidlMessage<::llcpp::fidl::test::llcpp::basictypes::TestInterface::ConsumeSimpleStructRequest> : public std::true_type {};
static_assert(sizeof(::llcpp::fidl::test::llcpp::basictypes::TestInterface::ConsumeSimpleStructRequest)
    == ::llcpp::fidl::test::llcpp::basictypes::TestInterface::ConsumeSimpleStructRequest::PrimarySize);
static_assert(offsetof(::llcpp::fidl::test::llcpp::basictypes::TestInterface::ConsumeSimpleStructRequest, arg) == 16);

template <>
struct IsFidlType<::llcpp::fidl::test::llcpp::basictypes::TestInterface::ConsumeSimpleStructResponse> : public std::true_type {};
template <>
struct IsFidlMessage<::llcpp::fidl::test::llcpp::basictypes::TestInterface::ConsumeSimpleStructResponse> : public std::true_type {};
static_assert(sizeof(::llcpp::fidl::test::llcpp::basictypes::TestInterface::ConsumeSimpleStructResponse)
    == ::llcpp::fidl::test::llcpp::basictypes::TestInterface::ConsumeSimpleStructResponse::PrimarySize);
static_assert(offsetof(::llcpp::fidl::test::llcpp::basictypes::TestInterface::ConsumeSimpleStructResponse, status) == 16);
static_assert(offsetof(::llcpp::fidl::test::llcpp::basictypes::TestInterface::ConsumeSimpleStructResponse, field) == 20);

}  // namespace fidl
