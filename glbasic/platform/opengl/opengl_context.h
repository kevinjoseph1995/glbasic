#pragma once
#include "glbasic/renderer/rendering_context.h"

namespace glbasic
{
class OpenGLContext : public RenderingContext
{
  public:
    void Init(GLFWwindow *window) override;
    void SwapBuffers() override;

  private:
    GLFWwindow *window_ = nullptr;
};
} // namespace glbasic
