//
// Created by kevin on 8/1/21.
//
#include "glbasic/renderer/rendering_context.h"
#include "opengl/opengl_context.h"

namespace glbasic
{
std::unique_ptr<RenderingContext> RenderingContext::Create()
{
    return std::make_unique<OpenGLContext>();
}

} // namespace glbasic
