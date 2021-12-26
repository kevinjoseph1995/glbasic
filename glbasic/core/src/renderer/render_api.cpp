//
// Created by kevin on 8/2/21.
//

#include "glbasic/renderer/render_api.h"
#include "opengl/opengl_render_api.h"
#include <memory>

namespace glbasic
{
// This will in the future become become a compile/runtime setup process
RenderAPI::API RenderAPI::api_ = RenderAPI::API::OpenGL;

std::unique_ptr<RenderAPI> RenderAPI::Create()
{
    return std::make_unique<OpenGLRenderAPI>();
}
} // namespace glbasic