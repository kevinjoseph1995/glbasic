//
// Created by kevin on 7/15/21.
//
#include "glbasic/renderer/vertex_array.h"
#include "opengl/opengl_vertex_array.h"

namespace glbasic
{
std::shared_ptr<VertexArray> VertexArray::Create()
{
    return std::make_shared<OpenGLVertexArray>();
}
} // namespace glbasic
