#include "opengl_context.h"

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on
#include "../../core/glbasic/gl_debug.h"
#include "spdlog/spdlog.h"

namespace glbasic
{
void OpenGLContext::Init(GLFWwindow *window)
{
    window_ = window;
    glfwMakeContextCurrent(window_);

    //  Load up OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        spdlog::critical("[OpenGLContext::Ini]Failed to initialize GLAD");
        GL_ASSERT(true, "[OpenGLContext::Init]");
    }
}

void OpenGLContext::SwapBuffers()
{
    glfwSwapBuffers(window_);
}

} // namespace glbasic
