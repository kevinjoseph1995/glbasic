#include "glbasic/renderer/renderer.h"
#include "glbasic/renderer/render_command.h"

#include "glm/gtc/type_ptr.hpp"

namespace glbasic
{

[[maybe_unused]] glm::mat4 Renderer::view_projection_ = glm::mat4(1.0f);

void Renderer::OnWindowResize(int32_t width, int32_t height)
{
    RenderCommand::SetViewport(0, 0, width, height);
}
void Renderer::Init()
{
    RenderCommand::Init();
}
void Renderer::Shutdown()
{
}
void Renderer::BeginScene(const Camera &camera)
{
    view_projection_ = camera.GetViewProjectionMatrix();
}
void Renderer::EndScene()
{
}
void Renderer::Submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertex_array,
                      const glm::mat4 &transform)
{
    shader->Bind();
    shader->SetUniformMat4f("model", glm::value_ptr(transform));
    shader->SetUniformMat4f("view_projection", glm::value_ptr(view_projection_));
    vertex_array->Bind();
    RenderCommand::DrawIndexed(vertex_array, vertex_array->GetIndexBuffer()->GetCount());
}

} // namespace glbasic
