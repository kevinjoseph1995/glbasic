#pragma once

#include "glbasic/renderer/shader.h"

#include <glm/vec4.hpp>
#include <string>
#include <unordered_map>

namespace glbasic
{
struct ShaderProgramSource
{
    std::string vertex_shader_source;
    std::string fragment_shader_source;
};

class OpenGLShader : public Shader
{
  public:
    [[nodiscard]] bool Init(const std::string &vertex_shader_src, const std::string &fragment_shader_src) override;
    void Bind() override;
    void UnBind() override;
    void SetUniformVec4f(const std::string &name, const glm::vec4 &vector) override;
    void SetUniform1i(const std::string &name, int32_t val) override;
    void SetUniformMat4f(const std::string &name, const float *data) override;
    ~OpenGLShader() override;

  private:
    [[nodiscard]] int32_t getUniformLocation(const std::string &name);
    [[nodiscard]] bool compileShaders();
    [[nodiscard]] bool compileShaderProgram();

  private:
    uint32_t id_ = 0;
    uint32_t vertex_shader_id_ = 0;
    uint32_t fragment_shader_id_ = 0;

    ShaderProgramSource src_;
    std::unordered_map<std::string, int32_t> uniform_cache_;
};

} // namespace glbasic