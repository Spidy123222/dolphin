// Copyright 2021 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include "VideoBackends/Metal/MetalTexture.h"

namespace Metal
{
MetalTexture::MetalTexture(const TextureConfig& tex_config) : AbstractTexture(tex_config)
{
}

void MetalTexture::CopyRectangleFromTexture(const AbstractTexture* src,
                                            const MathUtil::Rectangle<int>& src_rect, u32 src_layer,
                                            u32 src_level, const MathUtil::Rectangle<int>& dst_rect,
                                            u32 dst_layer, u32 dst_level)
{
}
void MetalTexture::ResolveFromTexture(const AbstractTexture* src,
                                      const MathUtil::Rectangle<int>& rect, u32 layer, u32 level)
{
}

void MetalTexture::Load(u32 level, u32 width, u32 height, u32 row_length, const u8* buffer,
                        size_t buffer_size)
{
}

MetalStagingTexture::MetalStagingTexture(StagingTextureType type, const TextureConfig& config)
    : AbstractStagingTexture(type, config)
{
  m_texture_buf.resize(m_texel_size * config.width * config.height);
  m_map_pointer = reinterpret_cast<char*>(m_texture_buf.data());
  m_map_stride = m_texel_size * config.width;
}

MetalStagingTexture::~MetalStagingTexture() = default;

void MetalStagingTexture::CopyFromTexture(const AbstractTexture* src,
                                          const MathUtil::Rectangle<int>& src_rect, u32 src_layer,
                                          u32 src_level, const MathUtil::Rectangle<int>& dst_rect)
{
  m_needs_flush = true;
}

void MetalStagingTexture::CopyToTexture(const MathUtil::Rectangle<int>& src_rect,
                                        AbstractTexture* dst,
                                        const MathUtil::Rectangle<int>& dst_rect, u32 dst_layer,
                                        u32 dst_level)
{
  m_needs_flush = true;
}

bool MetalStagingTexture::Map()
{
  return true;
}

void MetalStagingTexture::Unmap()
{
}

void MetalStagingTexture::Flush()
{
  m_needs_flush = false;
}

MetalFramebuffer::MetalFramebuffer(AbstractTexture* color_attachment,
                                   AbstractTexture* depth_attachment,
                                   AbstractTextureFormat color_format,
                                   AbstractTextureFormat depth_format, u32 width, u32 height,
                                   u32 layers, u32 samples)
    : AbstractFramebuffer(color_attachment, depth_attachment, color_format, depth_format, width,
                          height, layers, samples)
{
}

std::unique_ptr<MetalFramebuffer> MetalFramebuffer::Create(MetalTexture* color_attachment,
                                                           MetalTexture* depth_attachment)
{
  if (!ValidateConfig(color_attachment, depth_attachment))
    return nullptr;

  const AbstractTextureFormat color_format =
      color_attachment ? color_attachment->GetFormat() : AbstractTextureFormat::Undefined;
  const AbstractTextureFormat depth_format =
      depth_attachment ? depth_attachment->GetFormat() : AbstractTextureFormat::Undefined;
  const MetalTexture* either_attachment = color_attachment ? color_attachment : depth_attachment;
  const u32 width = either_attachment->GetWidth();
  const u32 height = either_attachment->GetHeight();
  const u32 layers = either_attachment->GetLayers();
  const u32 samples = either_attachment->GetSamples();

  return std::make_unique<MetalFramebuffer>(color_attachment, depth_attachment, color_format,
                                            depth_format, width, height, layers, samples);
}

}  // namespace Metal
