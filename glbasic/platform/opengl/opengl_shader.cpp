//
// Created by kevin on 7/22/21.
//

#include "opengl_shader.h"
#include "glad/glad.h"
#include "glbasic/gl_debug.h"
#include "glm/vec4.hpp"
#include "spdlog/spdlog.h"

#include <experimental/filesystem>
#include <fstream>

namespace glbasic
{
bool OpenGLShader::Init(const std::string &vertex_shader_src, const std::string &fragment_shader_src)
{
    src_.vertex_shader_source = vertex_shader_src;
    src_.fragment_shader_source = fragment_shader_src;
    if (!compileShaders())
        return false;
    if (!compileShaderProgram())
        return false;
    return true;
}
void OpenGLShader::Bind()
{
    GL_ASSERT(id_ != 0, "[OpenGLShader::Bind]");
    glUseProgram(id_);
}
void OpenGLShader::UnBind()
{
    GL_ASSERT(id_ != 0, "[OpenGLShader::Bind]");
    glUseProgram(0);
}
void OpenGLShader::SetUniformVec4f(const std::string &name, const glm::vec4 &v)
{
    GL_ASSERT(id_ != 0, "[OpenGLShader::SetUniformVec4f]");
    this->Bind();
    auto uniform = getUniformLocation(name);
    GL_ASSERT(uniform != -1, "[OpenGLShader::SetUniformVec4f]Invalid uniform location");
    glUniform4f(uniform, v.x, v.y, v.z, v.w);
}
void OpenGLShader::SetUniform1i(const std::string &name, int32_t val)
{
    GL_ASSERT(id_ != 0, "[ShaderProgram::SetUniform1i]");
    this->Bind();
    auto uniform = getUniformLocation(name);
    GL_ASSERT(uniform != -1, "[ShaderProgram::SetUniformVec4f]Invalid uniform location");
    glUniform1i(uniform, val);
}
void OpenGLShader::SetUniformMat4f(const std::string &name, const float *data)
{
    GL_ASSERT(id_ != 0, "[ShaderProgram::SetUniformMat4f]");
    this->Bind();
    auto uniform = getUniformLocation(name);
    GL_ASSERT(uniform != -1, "[ShaderProgram::SetUniformMat4f] Invalid uniform location");
    glUniformMatrix4fv(uniform, 1, GL_FALSE, data);
}
int32_t OpenGLShader::getUniformLocation(const std::string &name)
{
    GL_ASSERT(id_ != 0, "[OpenGLShader::getUniformLocation]");
    this->Bind();
    if (uniform_cache_.find(name) != uniform_cache_.end())
    {
        return uniform_cache_.at(name);
    }
    int32_t uniform_location = glGetUniformLocation(id_, name.c_str());
    if (uniform_location == -1)
    {
        spdlog::error("[OpenGLShader::GetUniformLocation]Uniform with name {0} not found "
                      "int program with id {1}",
                      name, id_);
    }
    else
    {
        uniform_cache_.insert({name, uniform_location});
    }
    return uniform_location;
}
bool OpenGLShader::compileShaders()
{
    GL_ASSERT(!src_.vertex_shader_source.empty(), "[OpenGLShader::compileShaders]: vertex_shader_source empty");
    GL_ASSERT(!src_.fragment_shader_source.empty(), "[OpenGLShader::compileShaders]: fragment_shader_source empty");

    vertex_shader_id_ = glCreateShader(GL_VERTEX_SHADER);
    std::array<const char *, 1> vertex_sources{src_.vertex_shader_source.c_str()};
    glShaderSource(vertex_shader_id_, 1, vertex_sources.data(), nullptr);
    glCompileShader(vertex_shader_id_);

    //  Check for any shader compilation error
    int32_t success;
    std::array<char, 512> infoLog{};
    glGetShaderiv(vertex_shader_id_, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex_shader_id_, infoLog.size(), nullptr, infoLog.data());
        spdlog::error("[OpenGLShader::compileShaders]Vertex Shader Compilation Info: {0}",
                      static_cast<char *>(&infoLog[0]));
        return false;
    }

    fragment_shader_id_ = glCreateShader(GL_FRAGMENT_SHADER);
    std::array<const char *, 1> fragment_sources{src_.fragment_shader_source.c_str()};
    glShaderSource(fragment_shader_id_, 1, fragment_sources.data(), nullptr);
    glCompileShader(fragment_shader_id_);

    glGetShaderiv(fragment_shader_id_, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment_shader_id_, infoLog.size(), nullptr, infoLog.data());
        spdlog::error("[OpenGLShader::compileShaders]Fragment Shader Compilation Info: {0}",
                      static_cast<char *>(&infoLog[0]));
        return false;
    }
    return true;
}
bool OpenGLShader::compileShaderProgram()
{
    id_ = glCreateProgram();
    glAttachShader(id_, vertex_shader_id_);
    glAttachShader(id_, fragment_shader_id_);
    glLinkProgram(id_);

    int32_t success;
    std::array<char, 512> infoLog{};
    glGetProgramiv(id_, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(id_, 512, nullptr, static_cast<char *>(&infoLog[0]));
        spdlog::error("[OpenGLShader::compileShaderProgram]Shader Program Linking Info: {0}",
                      static_cast<char *>(&infoLog[0]));
        return false;
    }
    glDeleteShader(vertex_shader_id_);
    vertex_shader_id_ = 0;
    glDeleteShader(fragment_shader_id_);
    fragment_shader_id_ = 0;
    return true;
}
OpenGLShader::~OpenGLShader()
{
    glDeleteProgram(id_);
}

} // namespace glbasic
