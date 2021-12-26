#pragma once

#include <memory>

struct GLFWwindow;

namespace glbasic
{
class RenderingContext
{
  public:
    virtual void Init(GLFWwindow *window) = 0;
    virtual void SwapBuffers() = 0;
    virtual ~RenderingContext() = default;
    static std::unique_ptr<RenderingContext> Create();
};
} // namespace glbasic