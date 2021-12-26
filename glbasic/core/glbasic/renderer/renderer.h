#pragma once

#include "glbasic/renderer/buffer.h"
#include "glbasic/renderer/camera.h"
#include "glbasic/renderer/render_api.h"
#include "glbasic/renderer/shader.h"
#include "glbasic/renderer/vertex_array.h"

namespace glbasic
{

class Renderer
{
  public:
    Renderer() = delete;
    static void Init();
    static void Shutdown();
    static void OnWindowResize(int32_t width, int32_t height);
    static void BeginScene(const Camera &camera);
    static void EndScene();

    static void Submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertex_array,
                       const glm::mat4 &transform = glm::mat4(1.0f));

    static RenderAPI::API GetAPI()
    {
        return RenderAPI::GetAPI();
    }

  private:
    static glm::mat4 view_projection_;
};
} // namespace glbasic
