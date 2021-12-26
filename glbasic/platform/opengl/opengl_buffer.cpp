//
// Created by kevin on 7/15/21.
//

#include "opengl_buffer.h"
#include "../../core/glbasic/gl_debug.h"

#include <glad/glad.h>

namespace glbasic
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////// Vertex Buffer //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
{

    glGenBuffers(1, &id_);
    glBindBuffer(GL_ARRAY_BUFFER, id_);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

OpenGLVertexBuffer::OpenGLVertexBuffer(const float *vertices, uint32_t size)
{

    glGenBuffers(1, &id_);
    glBindBuffer(GL_ARRAY_BUFFER, id_);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    glDeleteBuffers(1, &id_);
}

void OpenGLVertexBuffer::SetData(const float *vertices, uint32_t size) const
{
    GL_ASSERT(id_ != 0, "[OpenGLVertexBuffer::SetData]");
    glBindBuffer(GL_ARRAY_BUFFER, id_);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void OpenGLVertexBuffer::SetLayout(const BufferLayout &layout)
{
    layout_ = layout;
}
void OpenGLVertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, id_);
}
void OpenGLVertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
const BufferLayout &OpenGLVertexBuffer::GetLayout() const
{
    return layout_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////// Index Buffer ///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    glDeleteBuffers(1, &id_);
}
OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t *indices, int32_t count)
{
    glGenBuffers(1, &id_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * int64_t(sizeof(uint32_t)), indices, GL_STATIC_DRAW);
    count_ = count;
}

void OpenGLIndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void OpenGLIndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
}

int32_t OpenGLIndexBuffer::GetCount() const
{
    return count_;
}
} // namespace glbasic
