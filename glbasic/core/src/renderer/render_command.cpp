//
// Created by kevin on 8/2/21.
//
#include "glbasic/renderer/render_command.h"
#include "glbasic/renderer/render_api.h"

namespace glbasic
{
std::unique_ptr<RenderAPI> RenderCommand::render_api_ = RenderAPI::Create();
}
