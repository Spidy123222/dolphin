// Copyright 2021 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include "VideoBackends/Metal/MetalRender.h"

#include "VideoBackends/Metal/MetalTexture.h"

#include "VideoCommon/AbstractPipeline.h"
#include "VideoCommon/AbstractShader.h"
#include "VideoCommon/NativeVertexFormat.h"
#include "VideoCommon/VideoConfig.h"

namespace Metal
{
// Init functions
Renderer::Renderer() : ::Renderer(1, 1, 1.0f, AbstractTextureFormat::RGBA8)
{
  UpdateActiveConfig();
}

Renderer::~Renderer()
{
  UpdateActiveConfig();
}

bool Renderer::IsHeadless() const
{
  return true;
}

std::unique_ptr<AbstractTexture> Renderer::CreateTexture(const TextureConfig& config)
{
  return std::make_unique<MetalTexture>(config);
}

std::unique_ptr<AbstractStagingTexture> Renderer::CreateStagingTexture(StagingTextureType type,
                                                                       const TextureConfig& config)
{
  return std::make_unique<MetalStagingTexture>(type, config);
}

class MetalShader final : public AbstractShader
{
public:
  explicit MetalShader(ShaderStage stage) : AbstractShader(stage) {}
};

std::unique_ptr<AbstractShader>
Renderer::CreateShaderFromSource(ShaderStage stage, [[maybe_unused]] std::string_view source)
{
  return std::make_unique<MetalShader>(stage);
}

std::unique_ptr<AbstractShader> Renderer::CreateShaderFromBinary(ShaderStage stage,
                                                                 const void* data, size_t length)
{
  return std::make_unique<MetalShader>(stage);
}

class MetalPipeline final : public AbstractPipeline
{
};

std::unique_ptr<AbstractPipeline> Renderer::CreatePipeline(const AbstractPipelineConfig& config,
                                                           const void* cache_data,
                                                           size_t cache_data_length)
{
  return std::make_unique<MetalPipeline>();
}

std::unique_ptr<AbstractFramebuffer> Renderer::CreateFramebuffer(AbstractTexture* color_attachment,
                                                                 AbstractTexture* depth_attachment)
{
  return MetalFramebuffer::Create(static_cast<MetalTexture*>(color_attachment),
                                  static_cast<MetalTexture*>(depth_attachment));
}

std::unique_ptr<NativeVertexFormat>
Renderer::CreateNativeVertexFormat(const PortableVertexDeclaration& vtx_decl)
{
  return std::make_unique<NativeVertexFormat>(vtx_decl);
}
}  // namespace Metal
