//
// Created by kevin on 7/22/21.
//
#include "glbasic/renderer/shader.h"
#include "opengl/opengl_shader.h"
#include "spdlog/spdlog.h"
namespace glbasic
{
std::shared_ptr<Shader> glbasic::Shader::Create(const std::string &vertex_shader_src,
                                                const std::string &fragment_shader_src)
{
    std::shared_ptr<Shader> shader_program = std::make_shared<OpenGLShader>();
    if (shader_program->Init(vertex_shader_src, fragment_shader_src))
    {
        return shader_program;
    }
    else
    {
        spdlog::error("[glbasic::Shader::Create] Failed to create shader program");
        return nullptr;
    }
}
} // namespace glbasic
