//
// Created by kevin on 8/2/21.
//
#pragma once
#include "glbasic/renderer/render_api.h"

namespace glbasic
{
class OpenGLRenderAPI : public RenderAPI
{
  public:
    void Init() override;
    void SetViewport(int32_t x, int32_t y, int32_t width, int32_t height) override;
    void SetClearColor(const glm::vec4 &color) override;
    void Clear() override;
    void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray, int32_t indexCount) override;
};
} // namespace glbasic