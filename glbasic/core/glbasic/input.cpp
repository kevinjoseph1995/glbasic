//
// Created by kevin on 7/7/21.
//

#include "input.h"
#include "application.h"
#include "key_codes.h"
// clang-format off
#include "gl_debug.h"
#include "GLFW/glfw3.h"
// clang-format on

namespace glbasic
{
Input *Input::input_instance_ptr_ = nullptr;
Input::Input()
{
    GL_ASSERT(input_instance_ptr_ == nullptr, "[Input::Input(]Trying to create multiple instances of Input");
    input_instance_ptr_ = this;
}

bool Input::IsMouseButtonPressed(const int button)
{
    Application &app = Application::GetApplicationInstance();
    auto *window_manager = app.GetWindowManager();
    GLFWwindow *native_window = window_manager->GetNativeWindowHandle();
    auto state = glfwGetMouseButton(native_window, button);
    return state == GLFW_PRESS;
}

bool Input::IsMouseButtonReleased(const int button)
{
    Application &app = Application::GetApplicationInstance();
    auto *window_manager = app.GetWindowManager();
    GLFWwindow *native_window = window_manager->GetNativeWindowHandle();
    auto state = glfwGetMouseButton(native_window, button);
    return state == GLFW_RELEASE;
}

glm::vec2 Input::GetMousePosition()
{
    Application &app = Application::GetApplicationInstance();
    auto *window_manager = app.GetWindowManager();
    GLFWwindow *native_window = window_manager->GetNativeWindowHandle();
    double x_pos, y_pos;
    glfwGetCursorPos(native_window, &x_pos, &y_pos);
    return {static_cast<float>(x_pos), static_cast<float>(y_pos)};
}
bool Input::IsKeyPressed(KeyCode key)
{
    auto *native_window =
        static_cast<GLFWwindow *>(Application::GetApplicationInstance().GetWindowManager()->GetNativeWindowHandle());
    auto state = glfwGetKey(native_window, key);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

} // namespace glbasic