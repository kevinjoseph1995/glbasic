#pragma once
#include "glbasic/renderer/vertex_array.h"

#include <glm/gtc/matrix_transform.hpp>
#include <memory>

namespace glbasic
{

class RenderAPI
{
  public:
    enum class API
    {
        None = 0,
        OpenGL = 1
    };

  public:
    virtual ~RenderAPI() = default;

    virtual void Init() = 0;
    virtual void SetViewport(int32_t x, int32_t y, int32_t width, int32_t height) = 0;
    virtual void SetClearColor(const glm::vec4 &color) = 0;
    virtual void Clear() = 0;

    virtual void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray, int32_t indexCount) = 0;

    static API GetAPI()
    {
        return api_;
    }
    static std::unique_ptr<RenderAPI> Create();

  private:
    static API api_;
};

} // namespace glbasic
