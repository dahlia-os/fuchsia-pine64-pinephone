// Copyright 2019 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "src/media/audio/audio_core/testing/fake_audio_driver.h"

#include <audio-proto-utils/format-utils.h>
#include <gtest/gtest.h>

#include "src/lib/syslog/cpp/logger.h"

namespace media::audio::testing {

FakeAudioDriver::FakeAudioDriver(zx::channel channel, async_dispatcher_t* dispatcher) :
  dispatcher_(dispatcher),
  stream_binding_(this, std::move(channel), dispatcher) {
  formats_.number_of_channels.push_back(2);
  formats_.sample_formats.push_back(driver_fidl::SampleFormat::PCM_SIGNED);
  formats_.bytes_per_sample.push_back(2);
  formats_.valid_bits_per_sample.push_back(16);
  formats_.frame_rates.push_back(48000);
  Stop();
}

void FakeAudioDriver::Start() {
  assert(!stream_binding_.is_bound());
  stream_binding_.Bind(std::move(stream_req_), dispatcher_);
  if (ring_buffer_binding_.has_value() && !ring_buffer_binding_->is_bound()) {
    ring_buffer_binding_->Bind(std::move(ring_buffer_req_ ), dispatcher_);
  }
}

void FakeAudioDriver::Stop() {
  if (stream_binding_.is_bound()) {
    stream_req_ = stream_binding_.Unbind();
  }
  if (ring_buffer_binding_.has_value() && ring_buffer_binding_->is_bound()) {
    ring_buffer_req_ = ring_buffer_binding_->Unbind();
  }
}

fzl::VmoMapper FakeAudioDriver::CreateRingBuffer(size_t size) {
  FX_CHECK(!ring_buffer_) << "Calling CreateRingBuffer multiple times is not supported";

  ring_buffer_size_ = size;
  fzl::VmoMapper mapper;
  mapper.CreateAndMap(ring_buffer_size_, ZX_VM_PERM_READ | ZX_VM_PERM_WRITE, nullptr,
                      &ring_buffer_);
  return mapper;
}

void FakeAudioDriver::GetProperties(driver_fidl::StreamConfig::GetPropertiesCallback callback) {
  driver_fidl::StreamProperties props = {};

  std::memcpy(props.mutable_unique_id()->data(), uid_.data, sizeof(uid_.data));
  props.set_manufacturer(manufacturer_);
  props.set_product(product_);
  props.set_can_mute(can_mute_);
  props.set_can_agc(can_agc_);
  props.set_min_gain_db(gain_limits_.first);
  props.set_max_gain_db(gain_limits_.second);
  props.set_gain_step_db(0.001f);
  props.set_plug_detect_capabilities(driver_fidl::PlugDetectCapabilities::CAN_ASYNC_NOTIFY);

  callback(std::move(props));
}

void FakeAudioDriver::GetSupportedFormats(
  driver_fidl::StreamConfig::GetSupportedFormatsCallback callback) {
  driver_fidl::SupportedFormats formats = {};
  formats.set_pcm_supported_formats(formats_);

  std::vector<driver_fidl::SupportedFormats> all_formats = {};
  all_formats.push_back(std::move(formats));
  callback(std::move(all_formats));
}

void FakeAudioDriver::CreateRingBuffer(
  driver_fidl::Format format,
  ::fidl::InterfaceRequest<driver_fidl::RingBuffer> ring_buffer) {
  ring_buffer_binding_.emplace(this, ring_buffer.TakeChannel(), dispatcher_);
  selected_format_ = format.pcm_format();
}

void FakeAudioDriver::WatchGainState(driver_fidl::StreamConfig::WatchGainStateCallback callback) {
  driver_fidl::GainState gain_state = {};
  gain_state.set_muted(cur_mute_);
  gain_state.set_agc_enabled(cur_agc_);
  gain_state.set_gain_db(cur_gain_);
  callback(std::move(gain_state));
}

void FakeAudioDriver::SetGain(driver_fidl::GainState target_state) {
}

void FakeAudioDriver::WatchPlugState(driver_fidl::StreamConfig::WatchPlugStateCallback callback) {
  driver_fidl::PlugState plug_state = {};
  plug_state.set_plugged(true);
  plug_state.set_plug_state_time(0);
  callback(std::move(plug_state));
}

void FakeAudioDriver::GetProperties(driver_fidl::RingBuffer::GetPropertiesCallback callback) {
  driver_fidl::RingBufferProperties props = {};

  props.set_external_delay(0);
  props.set_fifo_depth(fifo_depth_);
  props.set_clock_domain(clock_domain_);
  props.set_needs_cache_flush_or_invalidate(false);

  callback(std::move(props));
}

void FakeAudioDriver::WatchClockRecoveryPositionInfo(
  driver_fidl::RingBuffer::WatchClockRecoveryPositionInfoCallback callback) {
}

void FakeAudioDriver::GetVmo(uint32_t min_frames, uint32_t clock_recovery_notifications_per_ring,
              driver_fidl::RingBuffer::GetVmoCallback callback) {

  // This should be true since it's set as part of creating the channel that's carrying these
  // messages.
  FX_CHECK(selected_format_);

  if (!ring_buffer_) {
    // If we haven't created a ring buffer, we'll just drop this request.
    return;
  }
  FX_CHECK(ring_buffer_);

  // Dup our ring buffer VMO to send over the channel.
  zx::vmo dup;
  FX_CHECK(ring_buffer_.duplicate(ZX_RIGHT_SAME_RIGHTS, &dup) == ZX_OK);

  // Compute the buffer size in frames.
  auto frame_size = selected_format_->number_of_channels * selected_format_->bytes_per_sample;
  auto ring_buffer_frames = ring_buffer_size_ / frame_size;

  driver_fidl::RingBuffer_GetVmo_Result result = {};
  driver_fidl::RingBuffer_GetVmo_Response response = {};
  response.num_frames = ring_buffer_frames;
  response.ring_buffer = std::move(dup);
  result.set_response(std::move(response));
  callback(std::move(result));
}

void FakeAudioDriver::Start(driver_fidl::RingBuffer::StartCallback callback) {
  EXPECT_TRUE(!is_running_);
  is_running_ = true;
  callback(async::Now(dispatcher_).get());
}

void FakeAudioDriver::Stop(driver_fidl::RingBuffer::StopCallback callback) {
  EXPECT_TRUE(is_running_);
  is_running_ = false;
  callback();
}

}  // namespace media::audio::testing
