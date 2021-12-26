#pragma once
#include <memory>

#include "glbasic/renderer/render_api.h"

namespace glbasic
{
class RenderCommand
{
  private:
    static std::unique_ptr<RenderAPI> render_api_;

  public:
    static void Init()
    {
        render_api_->Init();
    }

    static void SetViewport(int32_t x, int32_t y, int32_t width, int32_t height)
    {
        render_api_->SetViewport(x, y, width, height);
    }

    static void SetClearColor(const glm::vec4 &color)
    {
        render_api_->SetClearColor(color);
    }

    static void Clear()
    {
        render_api_->Clear();
    }

    static void DrawIndexed(const std::shared_ptr<VertexArray> &vertex_array, int32_t count = 0)
    {
        render_api_->DrawIndexed(vertex_array, count);
    }
};
} // namespace glbasic
