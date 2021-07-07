// Copyright 2021 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "VideoCommon/VertexManagerBase.h"

namespace Metal
{
class VertexManager final : public VertexManagerBase
{
public:
  VertexManager();
  ~VertexManager() override;

protected:
  void DrawCurrentBatch(u32 base_index, u32 num_indices, u32 base_vertex) override;
};
}  // namespace Metal
