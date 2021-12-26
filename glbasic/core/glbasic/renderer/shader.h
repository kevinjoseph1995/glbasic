#pragma once
#include "glm/vec4.hpp"
#include <memory>
#include <string>

namespace glbasic
{
class Shader
{
  public:
    [[nodiscard]] virtual bool Init(const std::string &vertex_shader_src, const std::string &fragment_shader_src) = 0;
    virtual void Bind() = 0;
    virtual void UnBind() = 0;
    virtual void SetUniformVec4f(const std::string &name, const glm::vec4 &v)
    {
        (void)name;
        (void)v;
    };
    virtual void SetUniform1i(const std::string &name, int32_t val)
    {
        (void)name;
        (void)val;
    };
    virtual void SetUniformMat4f(const std::string &name, const float *data)
    {
        (void)name;
        (void)data;
    };
    virtual ~Shader() = default;

    static std::shared_ptr<Shader> Create(const std::string &vertex_shader_src, const std::string &fragment_shader_src);
};
} // namespace glbasic
