#include "glbasic/renderer/buffer.h"
#include "opengl/opengl_buffer.h"
#include <memory>
//
// Created by kevin on 7/15/21.
//
namespace glbasic
{
std::shared_ptr<VertexBuffer> VertexBuffer::Create(uint32_t size)
{
    return std::make_shared<OpenGLVertexBuffer>(size);
}
std::shared_ptr<VertexBuffer> VertexBuffer::Create(const float *vertices, uint32_t size)
{
    return std::make_shared<OpenGLVertexBuffer>(vertices, size);
}

std::shared_ptr<IndexBuffer> IndexBuffer::Create(const uint32_t *indices, int32_t count)
{
    return std::make_shared<OpenGLIndexBuffer>(indices, count);
}

} // namespace glbasic
