// Copyright 2021 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "VideoCommon/VideoBackendBase.h"

namespace Metal
{
class VideoBackend final : public VideoBackendBase
{
public:
  bool Initialize(const WindowSystemInfo& wsi) override;
  void Shutdown() override;

  std::string GetName() const override { return NAME; }
  std::string GetDisplayName() const override;
  void InitBackendInfo() override;

  static constexpr const char* NAME = "Metal";
};
}  // namespace Metal
