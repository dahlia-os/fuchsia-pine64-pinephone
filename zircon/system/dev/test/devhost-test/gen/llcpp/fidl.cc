// WARNING: This file is machine generated by fidlgen.

#include <fuchsia/device/devhost/test/llcpp/fidl.h>
#include <memory>

namespace llcpp {

namespace fuchsia {
namespace device {
namespace devhost {
namespace test {

::llcpp::fuchsia::device::devhost::test::TestDevice_AddChildDevice_Result::TestDevice_AddChildDevice_Result() {
  tag_ = Tag::Invalid;
}

::llcpp::fuchsia::device::devhost::test::TestDevice_AddChildDevice_Result::~TestDevice_AddChildDevice_Result() {
  Destroy();
}

void ::llcpp::fuchsia::device::devhost::test::TestDevice_AddChildDevice_Result::Destroy() {
  switch (which()) {
  case Tag::kResponse:
    response_.~TestDevice_AddChildDevice_Response();
    break;
  default:
    break;
  }
  tag_ = Tag::Invalid;
}

void ::llcpp::fuchsia::device::devhost::test::TestDevice_AddChildDevice_Result::MoveImpl_(TestDevice_AddChildDevice_Result&& other) {
  switch (other.which()) {
  case Tag::kResponse:
    mutable_response() = std::move(other.mutable_response());
    break;
  case Tag::kErr:
    mutable_err() = std::move(other.mutable_err());
    break;
  default:
    break;
  }
  other.Destroy();
}

void ::llcpp::fuchsia::device::devhost::test::TestDevice_AddChildDevice_Result::SizeAndOffsetAssertionHelper() {
  static_assert(offsetof(::llcpp::fuchsia::device::devhost::test::TestDevice_AddChildDevice_Result, response_) == 4);
  static_assert(offsetof(::llcpp::fuchsia::device::devhost::test::TestDevice_AddChildDevice_Result, err_) == 4);
  static_assert(sizeof(::llcpp::fuchsia::device::devhost::test::TestDevice_AddChildDevice_Result) == ::llcpp::fuchsia::device::devhost::test::TestDevice_AddChildDevice_Result::PrimarySize);
}


::llcpp::fuchsia::device::devhost::test::TestDevice_AddChildDevice_Response& ::llcpp::fuchsia::device::devhost::test::TestDevice_AddChildDevice_Result::mutable_response() {
  if (which() != Tag::kResponse) {
    Destroy();
    new (&response_) ::llcpp::fuchsia::device::devhost::test::TestDevice_AddChildDevice_Response;
  }
  tag_ = Tag::kResponse;
  return response_;
}

int32_t& ::llcpp::fuchsia::device::devhost::test::TestDevice_AddChildDevice_Result::mutable_err() {
  if (which() != Tag::kErr) {
    Destroy();
    new (&err_) int32_t;
  }
  tag_ = Tag::kErr;
  return err_;
}


namespace {

[[maybe_unused]]
constexpr uint64_t kTestDevice_AddChildDevice_Ordinal = 0x1164758100000000lu;
[[maybe_unused]]
constexpr uint64_t kTestDevice_AddChildDevice_GenOrdinal = 0x556f822500b898eclu;
extern "C" const fidl_type_t fuchsia_device_devhost_test_TestDeviceAddChildDeviceResponseTable;

}  // namespace
template <>
TestDevice::ResultOf::AddChildDevice_Impl<TestDevice::AddChildDeviceResponse>::AddChildDevice_Impl(zx::unowned_channel _client_end) {
  constexpr uint32_t _kWriteAllocSize = ::fidl::internal::ClampedMessageSize<AddChildDeviceRequest, ::fidl::MessageDirection::kSending>();
  ::fidl::internal::AlignedBuffer<_kWriteAllocSize> _write_bytes_inlined;
  auto& _write_bytes_array = _write_bytes_inlined;
  uint8_t* _write_bytes = _write_bytes_array.view().data();
  memset(_write_bytes, 0, AddChildDeviceRequest::PrimarySize);
  ::fidl::BytePart _request_bytes(_write_bytes, _kWriteAllocSize, sizeof(AddChildDeviceRequest));
  ::fidl::DecodedMessage<AddChildDeviceRequest> _decoded_request(std::move(_request_bytes));
  Super::SetResult(
      TestDevice::InPlace::AddChildDevice(std::move(_client_end), Super::response_buffer()));
}

TestDevice::ResultOf::AddChildDevice TestDevice::SyncClient::AddChildDevice() {
  return ResultOf::AddChildDevice(zx::unowned_channel(this->channel_));
}

TestDevice::ResultOf::AddChildDevice TestDevice::Call::AddChildDevice(zx::unowned_channel _client_end) {
  return ResultOf::AddChildDevice(std::move(_client_end));
}

template <>
TestDevice::UnownedResultOf::AddChildDevice_Impl<TestDevice::AddChildDeviceResponse>::AddChildDevice_Impl(zx::unowned_channel _client_end, ::fidl::BytePart _response_buffer) {
  FIDL_ALIGNDECL uint8_t _write_bytes[sizeof(AddChildDeviceRequest)] = {};
  ::fidl::BytePart _request_buffer(_write_bytes, sizeof(_write_bytes));
  memset(_request_buffer.data(), 0, AddChildDeviceRequest::PrimarySize);
  _request_buffer.set_actual(sizeof(AddChildDeviceRequest));
  ::fidl::DecodedMessage<AddChildDeviceRequest> _decoded_request(std::move(_request_buffer));
  Super::SetResult(
      TestDevice::InPlace::AddChildDevice(std::move(_client_end), std::move(_response_buffer)));
}

TestDevice::UnownedResultOf::AddChildDevice TestDevice::SyncClient::AddChildDevice(::fidl::BytePart _response_buffer) {
  return UnownedResultOf::AddChildDevice(zx::unowned_channel(this->channel_), std::move(_response_buffer));
}

TestDevice::UnownedResultOf::AddChildDevice TestDevice::Call::AddChildDevice(zx::unowned_channel _client_end, ::fidl::BytePart _response_buffer) {
  return UnownedResultOf::AddChildDevice(std::move(_client_end), std::move(_response_buffer));
}

::fidl::DecodeResult<TestDevice::AddChildDeviceResponse> TestDevice::InPlace::AddChildDevice(zx::unowned_channel _client_end, ::fidl::BytePart response_buffer) {
  constexpr uint32_t _write_num_bytes = sizeof(AddChildDeviceRequest);
  ::fidl::internal::AlignedBuffer<_write_num_bytes> _write_bytes;
  ::fidl::BytePart _request_buffer = _write_bytes.view();
  _request_buffer.set_actual(_write_num_bytes);
  ::fidl::DecodedMessage<AddChildDeviceRequest> params(std::move(_request_buffer));
  TestDevice::SetTransactionHeaderFor::AddChildDeviceRequest(params);
  auto _encode_request_result = ::fidl::Encode(std::move(params));
  if (_encode_request_result.status != ZX_OK) {
    return ::fidl::DecodeResult<TestDevice::AddChildDeviceResponse>::FromFailure(
        std::move(_encode_request_result));
  }
  auto _call_result = ::fidl::Call<AddChildDeviceRequest, AddChildDeviceResponse>(
    std::move(_client_end), std::move(_encode_request_result.message), std::move(response_buffer));
  if (_call_result.status != ZX_OK) {
    return ::fidl::DecodeResult<TestDevice::AddChildDeviceResponse>::FromFailure(
        std::move(_call_result));
  }
  return ::fidl::Decode(std::move(_call_result.message));
}


bool TestDevice::TryDispatch(Interface* impl, fidl_msg_t* msg, ::fidl::Transaction* txn) {
  if (msg->num_bytes < sizeof(fidl_message_header_t)) {
    zx_handle_close_many(msg->handles, msg->num_handles);
    txn->Close(ZX_ERR_INVALID_ARGS);
    return true;
  }
  fidl_message_header_t* hdr = reinterpret_cast<fidl_message_header_t*>(msg->bytes);
  switch (hdr->ordinal) {
    case kTestDevice_AddChildDevice_Ordinal:
    case kTestDevice_AddChildDevice_GenOrdinal:
    {
      auto result = ::fidl::DecodeAs<AddChildDeviceRequest>(msg);
      if (result.status != ZX_OK) {
        txn->Close(ZX_ERR_INVALID_ARGS);
        return true;
      }
      impl->AddChildDevice(
        Interface::AddChildDeviceCompleter::Sync(txn));
      return true;
    }
    default: {
      return false;
    }
  }
}

bool TestDevice::Dispatch(Interface* impl, fidl_msg_t* msg, ::fidl::Transaction* txn) {
  bool found = TryDispatch(impl, msg, txn);
  if (!found) {
    zx_handle_close_many(msg->handles, msg->num_handles);
    txn->Close(ZX_ERR_NOT_SUPPORTED);
  }
  return found;
}


void TestDevice::Interface::AddChildDeviceCompleterBase::Reply(::llcpp::fuchsia::device::devhost::test::TestDevice_AddChildDevice_Result result) {
  constexpr uint32_t _kWriteAllocSize = ::fidl::internal::ClampedMessageSize<AddChildDeviceResponse, ::fidl::MessageDirection::kSending>();
  FIDL_ALIGNDECL uint8_t _write_bytes[_kWriteAllocSize] = {};
  auto& _response = *reinterpret_cast<AddChildDeviceResponse*>(_write_bytes);
  TestDevice::SetTransactionHeaderFor::AddChildDeviceResponse(
      ::fidl::DecodedMessage<AddChildDeviceResponse>(
          ::fidl::BytePart(reinterpret_cast<uint8_t*>(&_response),
              AddChildDeviceResponse::PrimarySize,
              AddChildDeviceResponse::PrimarySize)));
  _response.result = std::move(result);
  ::fidl::BytePart _response_bytes(_write_bytes, _kWriteAllocSize, sizeof(AddChildDeviceResponse));
  CompleterBase::SendReply(::fidl::DecodedMessage<AddChildDeviceResponse>(std::move(_response_bytes)));
}
void TestDevice::Interface::AddChildDeviceCompleterBase::ReplySuccess() {
  TestDevice_AddChildDevice_Response response;

  Reply(TestDevice_AddChildDevice_Result::WithResponse(std::move(response)));
}
void TestDevice::Interface::AddChildDeviceCompleterBase::ReplyError(int32_t error) {
  Reply(TestDevice_AddChildDevice_Result::WithErr(std::move(error)));
}

void TestDevice::Interface::AddChildDeviceCompleterBase::Reply(::fidl::BytePart _buffer, ::llcpp::fuchsia::device::devhost::test::TestDevice_AddChildDevice_Result result) {
  if (_buffer.capacity() < AddChildDeviceResponse::PrimarySize) {
    CompleterBase::Close(ZX_ERR_INTERNAL);
    return;
  }
  auto& _response = *reinterpret_cast<AddChildDeviceResponse*>(_buffer.data());
  TestDevice::SetTransactionHeaderFor::AddChildDeviceResponse(
      ::fidl::DecodedMessage<AddChildDeviceResponse>(
          ::fidl::BytePart(reinterpret_cast<uint8_t*>(&_response),
              AddChildDeviceResponse::PrimarySize,
              AddChildDeviceResponse::PrimarySize)));
  _response.result = std::move(result);
  _buffer.set_actual(sizeof(AddChildDeviceResponse));
  CompleterBase::SendReply(::fidl::DecodedMessage<AddChildDeviceResponse>(std::move(_buffer)));
}
void TestDevice::Interface::AddChildDeviceCompleterBase::ReplySuccess(::fidl::BytePart _buffer) {
  TestDevice_AddChildDevice_Response response;

  Reply(std::move(_buffer), TestDevice_AddChildDevice_Result::WithResponse(std::move(response)));
}

void TestDevice::Interface::AddChildDeviceCompleterBase::Reply(::fidl::DecodedMessage<AddChildDeviceResponse> params) {
  TestDevice::SetTransactionHeaderFor::AddChildDeviceResponse(params);
  CompleterBase::SendReply(std::move(params));
}



void TestDevice::SetTransactionHeaderFor::AddChildDeviceRequest(const ::fidl::DecodedMessage<TestDevice::AddChildDeviceRequest>& _msg) {
  fidl_init_txn_header(&_msg.message()->_hdr, 0, kTestDevice_AddChildDevice_Ordinal);
}
void TestDevice::SetTransactionHeaderFor::AddChildDeviceResponse(const ::fidl::DecodedMessage<TestDevice::AddChildDeviceResponse>& _msg) {
  fidl_init_txn_header(&_msg.message()->_hdr, 0, kTestDevice_AddChildDevice_Ordinal);
}

}  // namespace test
}  // namespace devhost
}  // namespace device
}  // namespace fuchsia
}  // namespace llcpp
