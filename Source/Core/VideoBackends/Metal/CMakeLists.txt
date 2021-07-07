add_library(videometal
  MetalBackend.cpp
  MetalRender.cpp
  MetalRender.h
  MetalTexture.cpp
  MetalTexture.h
  MetalVertexManager.cpp
  MetalVertexManager.h
  PerfQuery.h
  TextureCache.h
  VideoBackend.h
)

target_link_libraries(videometal
PUBLIC
  common
  videocommon
)
