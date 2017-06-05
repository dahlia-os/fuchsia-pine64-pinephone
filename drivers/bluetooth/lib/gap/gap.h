// Copyright 2017 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <cstdint>

// This file contains constants and numbers that are part of the Generic Access
// Profile specification.

namespace bluetooth {
namespace gap {

// Bluetooth technologies that a device can support.
enum class TechnologyType {
  kLowEnergy,
  kClassic,
  kDualMode,
};

// EIR Data Type, Advertising Data Type (AD Type), OOB Data Type definitions.
enum class DataType : uint8_t {
  kFlags                        = 0x01,
  kIncomplete16BitServiceUUIDs  = 0x02,
  kComplete16BitServiceUUIDs    = 0x03,
  kIncomplete32BitServiceUUIDs  = 0x04,
  kComplete32BitServiceUUIDs    = 0x05,
  kIncomplete128BitServiceUUIDs = 0x06,
  kComplete128BitServiceUUIDs   = 0x07,
  kShortenedLocalName           = 0x08,
  kCompleteLocalName            = 0x09,
  kTxPowerLevel                 = 0x0A,
  kClassOfDevice                = 0x0D,
  kSSPOOBHash                   = 0x0E,
  kSSPOOBRandomizer             = 0x0F,
  kAppearance                   = 0x19,
  kManufacturerSpecificData     = 0xFF,

  // TODO(armansito): Complete this list.
};

// Constants for the expected size (in octets) of an advertising/EIR/scan-response data field.
//
//  * If a constant contains the word "Min", then it specifies a minimum expected length rather than
//    an exact length.
//
//  * If a constants contains the word "ElemSize", then the data field is expected to contain a
//    contiguous array of elements of the specified size.
constexpr size_t kTxPowerLevelSize = 1;

constexpr size_t kFlagsSizeMin = 1;
constexpr size_t kManufacturerSpecificDataSizeMin = 2;

constexpr size_t k16BitUUIDElemSize = 2;
constexpr size_t k32BitUUIDElemSize = 4;
constexpr size_t k128BitUUIDElemSize = 16;

// Potential values that can be provided in the "Flags" advertising data
// bitfield.
enum AdvFlag : uint8_t {
  // Octet 0
  kLELimitedDiscoverableMode        = (1 << 0),
  kLEGeneralDiscoverableMode        = (1 << 1),
  kBREDRNotSupported                = (1 << 2),
  kSimultaneousLEAndBREDRController = (1 << 3),
  kSimultaneousLEAndBREDRHost       = (1 << 4),
};

// Constants used in Low Energy Discovery (see Core Spec v5.0, Vol 3, Part C, Appendix A).
constexpr int64_t kLEGeneralDiscoveryScanMinMs = 10240;       // 10.24 seconds
constexpr int64_t kLEGeneralDiscoveryScanMinCodedMs = 30720;  // 30.72 seconds
constexpr int64_t kLEScanFastPeriodMs = 30720;                // 30.72 seconds

// Recommended scan parameters that can be passed directly to the HCI commands. The HCI spec defines
// the time conversion as follows: Time =  N * 0.625 ms, where N is the value of the constant.
//
// A constant that contans the word "Coded" is recommended when using the LE Coded PHY. Otherwise
// the constant is recommended when using the LE 1M PHY.

// For user-initiated scanning
constexpr uint16_t kLEScanFastInterval = 0x0060;       // 60 ms
constexpr uint16_t kLEScanFastIntervalCoded = 0x0120;  // 180 ms
constexpr uint16_t kLEScanFastWindow = 0x0030;         // 30 ms
constexpr uint16_t kLEScanFastWindowCoded = 0x90;      // 90 ms

// For background scanning
constexpr uint16_t kLEScanSlowInterval1 = 0x0800;       // 1.28 s
constexpr uint16_t kLEScanSlowInterval1Coded = 0x1800;  // 3.84 s
constexpr uint16_t kLEScanSlowWindow1 = 0x0012;         // 11.25 ms
constexpr uint16_t kLEScanSlowWindow1Coded = 0x0036;    // 33.75 ms
constexpr uint16_t kLEScanSlowInterval2 = 0x1000;       // 2.56 s
constexpr uint16_t kLEScanSlowInterval2Coded = 0x3000;  // 7.68 s
constexpr uint16_t kLEScanSlowWindow2 = 0x0024;         // 22.5 ms
constexpr uint16_t kLEScanSlowWindow2Coded = 0x006C;    // 67.5 ms

}  // namespace gap
}  // namespace bluetooth
