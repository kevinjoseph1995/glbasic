//
// Created by kevin on 8/2/21.
//
#include "render_command.h"
#include "render_api.h"

namespace glbasic
{
std::unique_ptr<RenderAPI> RenderCommand::render_api_ = RenderAPI::Create();
}
