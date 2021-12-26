//
// Created by kevin on 9/29/21.
//

#ifndef GL_BASIC_CUBE
#define GL_BASIC_CUBE

#include "glbasic/renderer/buffer.h"
#include "glbasic/renderer/shader.h"
#include "glbasic/renderer/vertex_array.h"
#include "glm/mat4x4.hpp"
#include "glm/vec4.hpp"

namespace glbasic
{
class Cube
{
  public:
    [[nodiscard]] bool Initialize(const glm::mat4 &Tw_o, float side_length, const glm::vec4 &rgba);
    [[nodiscard]] std::shared_ptr<VertexArray> GetVAO()
    {
        GL_ASSERT(initialized_, "[GetVAO]Cube not initialized");
        return vao_;
    }
    [[nodiscard]] std::shared_ptr<Shader> GetShader()
    {
        GL_ASSERT(initialized_, "[GetShader]Cube not initialized");
        return shader_;
    }

  private:
    bool initialized_ = false;

    glm::mat4 Tw_o_ = glm::mat4(1.0f); // Transform which takes from object/model coordinates to world coordinates
    float side_length_ = 1.0f;
    glm::vec4 rgba_;

    std::shared_ptr<VertexArray> vao_ = nullptr;
    std::shared_ptr<VertexBuffer> vbo_ = nullptr;
    std::shared_ptr<IndexBuffer> ibo_ = nullptr;
    std::shared_ptr<Shader> shader_ = nullptr;
};
} // namespace glbasic

#endif // GL_BASIC_CUBE
