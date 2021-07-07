// Copyright 2021 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <memory>
#include <vector>

#include "Common/CommonTypes.h"

#include "VideoCommon/AbstractFramebuffer.h"
#include "VideoCommon/AbstractStagingTexture.h"
#include "VideoCommon/AbstractTexture.h"

namespace Metal
{
class MetalTexture final : public AbstractTexture
{
public:
  explicit MetalTexture(const TextureConfig& config);

  void CopyRectangleFromTexture(const AbstractTexture* src,
                                const MathUtil::Rectangle<int>& src_rect, u32 src_layer,
                                u32 src_level, const MathUtil::Rectangle<int>& dst_rect,
                                u32 dst_layer, u32 dst_level) override;
  void ResolveFromTexture(const AbstractTexture* src, const MathUtil::Rectangle<int>& rect,
                          u32 layer, u32 level) override;
  void Load(u32 level, u32 width, u32 height, u32 row_length, const u8* buffer,
            size_t buffer_size) override;
};

class MetalStagingTexture final : public AbstractStagingTexture
{
public:
  explicit MetalStagingTexture(StagingTextureType type, const TextureConfig& config);
  ~MetalStagingTexture();

  void CopyFromTexture(const AbstractTexture* src, const MathUtil::Rectangle<int>& src_rect,
                       u32 src_layer, u32 src_level,
                       const MathUtil::Rectangle<int>& dst_rect) override;
  void CopyToTexture(const MathUtil::Rectangle<int>& src_rect, AbstractTexture* dst,
                     const MathUtil::Rectangle<int>& dst_rect, u32 dst_layer,
                     u32 dst_level) override;

  bool Map() override;
  void Unmap() override;
  void Flush() override;

private:
  std::vector<u8> m_texture_buf;
};

class MetalFramebuffer final : public AbstractFramebuffer
{
public:
  explicit MetalFramebuffer(AbstractTexture* color_attachment, AbstractTexture* depth_attachment,
                            AbstractTextureFormat color_format, AbstractTextureFormat depth_format,
                            u32 width, u32 height, u32 layers, u32 samples);

  static std::unique_ptr<MetalFramebuffer> Create(MetalTexture* color_attachment,
                                                  MetalTexture* depth_attachment);
};

}  // namespace Metal
