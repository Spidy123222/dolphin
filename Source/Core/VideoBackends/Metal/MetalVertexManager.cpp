// Copyright 2021 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include "VideoBackends/Metal/MetalVertexManager.h"

namespace Metal
{
VertexManager::VertexManager() = default;

VertexManager::~VertexManager() = default;

void VertexManager::DrawCurrentBatch(u32 base_index, u32 num_indices, u32 base_vertex)
{
}

}  // namespace Metal
