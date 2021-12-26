//
// Created by kevin on 9/29/21.
//
#include "glbasic/objects/cube.h"
#include "glm/gtc/type_ptr.hpp"
#include "spdlog/spdlog.h"
#include <cstddef>

static constexpr char const *cube_vertex_shader_src = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 view_projection;
uniform mat4 model;

void main()
{
    gl_Position = view_projection * model * vec4(aPos, 1.0);
}
)";

static constexpr char const *cube_fragment_shader_src = R"(
#version 330 core

uniform vec4 frag_color;
out vec4 gl_FragColor;

void main()
{
    gl_FragColor =  frag_color;
}
)";

bool glbasic::Cube::Initialize(const glm::mat4 &Tw_o, const float side_length, const glm::vec4 &rgba)
{
    Tw_o_ = Tw_o;
    rgba_ = rgba;
    side_length_ = side_length;
    GL_ASSERT(side_length > 0.0f, "[glbasic::Cube::Initialize] side_length cannot be negative");

    ///////////////////////////////////////////Setup geometry///////////////////////////////////////////////////////////
    const auto half_side_length = side_length_ / 2.0f;
    // clang-format off
    const std::array<float, static_cast<std::size_t>(4 * 3 * 6)> vertices= {
      // Front face
               -half_side_length,  half_side_length,  half_side_length,
                half_side_length,  half_side_length, half_side_length,
                half_side_length, -half_side_length, half_side_length,
               -half_side_length, -half_side_length, half_side_length,
                // Back face
               -half_side_length,  half_side_length,  -half_side_length,
                half_side_length,  half_side_length, -half_side_length,
                half_side_length, -half_side_length, -half_side_length,
               -half_side_length, -half_side_length, -half_side_length,
               // Right face
                half_side_length,  half_side_length,  half_side_length,
                half_side_length,  half_side_length, -half_side_length,
                half_side_length, -half_side_length, -half_side_length,
                half_side_length, -half_side_length,  half_side_length,
                // Left face
               -half_side_length,  half_side_length,  half_side_length,
               -half_side_length,  half_side_length, -half_side_length,
               -half_side_length, -half_side_length, -half_side_length,
               -half_side_length, -half_side_length,  half_side_length,
               // Top face
               -half_side_length,  half_side_length,  half_side_length,
               -half_side_length,  half_side_length, -half_side_length,
                half_side_length,  half_side_length, -half_side_length,
                half_side_length,  half_side_length,  half_side_length,
                // Bottom face
               -half_side_length,  -half_side_length,  half_side_length,
               -half_side_length,  -half_side_length, -half_side_length,
                half_side_length,  -half_side_length, -half_side_length,
                half_side_length,  -half_side_length,  half_side_length
    };
    // clang-format on
    vao_ = glbasic::VertexArray::Create();
    vao_->Bind();
    // Create VBO
    vbo_ = glbasic::VertexBuffer::Create(vertices.data(), sizeof(vertices[0]) * vertices.size());
    vbo_->SetLayout({{glbasic::ShaderDataType::Float3, "Position"}});
    // Create IBO
    std::array<uint32_t, 36> indices = {0, 1, 2, 2, 0, 3};
    for (int i = 1; i < 6; i++)
    {
        for (int j = 0; j < 6; ++j)
        {
            // Filling in the other rows
            indices[i * 6 + j] = (indices[j] + i * 4);
        }
    }
    ibo_ = glbasic::IndexBuffer::Create(indices.data(), (int)indices.size());
    // Bind everything
    vao_->AddVertexBuffer(vbo_);
    vao_->SetIndexBuffer(ibo_);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    shader_ = Shader::Create(cube_vertex_shader_src, cube_fragment_shader_src);
    if (!shader_)
    {
        spdlog::error("[Cube::Initialize] Failed to compile shader");
        return false;
    }

    shader_->SetUniformMat4f("model", glm::value_ptr(Tw_o_));
    shader_->SetUniformVec4f("frag_color", rgba_);

    initialized_ = true;
    return initialized_;
}
