//
// Created by kevin on 7/15/21.
//

#include "opengl_vertex_array.h"
#include <glad/glad.h>

namespace glbasic
{
static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
{
    switch (type)
    {
    case ShaderDataType::Float:
    case ShaderDataType::Float2:
    case ShaderDataType::Float3:
    case ShaderDataType::Float4:
    case ShaderDataType::Mat3:
    case ShaderDataType::Mat4:
        return GL_FLOAT;
    case ShaderDataType::Int:
    case ShaderDataType::Int2:
    case ShaderDataType::Int3:
    case ShaderDataType::Int4:
        return GL_INT;
    case ShaderDataType::Bool:
        return GL_BOOL;
    case ShaderDataType::None:
        GL_ASSERT(false, "Unknown ShaderDataType!");
    }

    GL_ASSERT(false, "Unknown ShaderDataType!");
    return 0;
}

OpenGLVertexArray::OpenGLVertexArray()
{
    glGenVertexArrays(1, &id_);
}

OpenGLVertexArray::~OpenGLVertexArray()
{
    glDeleteVertexArrays(1, &id_);
}

void OpenGLVertexArray::Bind() const
{
    glBindVertexArray(id_);
}

void OpenGLVertexArray::Unbind() const
{
    glBindVertexArray(0);
}

void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer)
{

    GL_ASSERT(!vertexBuffer->GetLayout().GetElements().empty(),
              "[OpenGLVertexArray::AddVertexBuffer]Vertex Buffer has no layout!");

    glBindVertexArray(id_);
    vertexBuffer->Bind();

    const auto &layout = vertexBuffer->GetLayout();

    uint32_t buffer_idx = 0;
    for (const auto &element : layout)
    {
        switch (element.type)
        {
        case ShaderDataType::Float:
        case ShaderDataType::Float2:
        case ShaderDataType::Float3:
        case ShaderDataType::Float4: {
            glEnableVertexAttribArray(buffer_idx);
            glVertexAttribPointer(buffer_idx, static_cast<int32_t>(element.GetComponentCount()),
                                  ShaderDataTypeToOpenGLBaseType(element.type), element.normalized ? GL_TRUE : GL_FALSE,
                                  static_cast<int32_t>(layout.GetStride()), (const void *)element.offset);
            buffer_idx++;
            break;
        }
        case ShaderDataType::Int:
        case ShaderDataType::Int2:
        case ShaderDataType::Int3:
        case ShaderDataType::Int4:
        case ShaderDataType::Bool: {
            glEnableVertexAttribArray(buffer_idx);
            glVertexAttribIPointer(buffer_idx, static_cast<int32_t>(element.GetComponentCount()),
                                   ShaderDataTypeToOpenGLBaseType(element.type),
                                   static_cast<int32_t>(layout.GetStride()), (const void *)element.offset);
            buffer_idx++;
            break;
        }
        case ShaderDataType::Mat3:
        case ShaderDataType::Mat4: {
            const auto count = element.GetComponentCount();
            for (uint8_t i = 0; i < count; i++)
            {
                glEnableVertexAttribArray(buffer_idx);
                glVertexAttribPointer(buffer_idx, count, ShaderDataTypeToOpenGLBaseType(element.type),
                                      element.normalized ? GL_TRUE : GL_FALSE, static_cast<int32_t>(layout.GetStride()),
                                      (const void *)(element.offset + sizeof(float) * count * i));
                glVertexAttribDivisor(buffer_idx, 1);
                buffer_idx++;
            }
            break;
        }
        default:
            GL_ASSERT(false, "Unknown ShaderDataType!");
        }
    }

    vertex_buffers_.push_back(vertexBuffer);
}

void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer)
{
    glBindVertexArray(id_);
    indexBuffer->Bind();
    index_buffer_ = indexBuffer;
}
} // namespace glbasic