#pragma once

#include "glbasic/events/event.h"
#include "glbasic/gl_debug.h"
#include "glbasic/input.h"
#include "glbasic/renderer/rendering_context.h"

#include <functional>
#include <memory>
#include <string>

struct GLFWwindow;

struct ImGuiContext;

namespace glbasic
{
class WindowManager
{
  public:
    [[nodiscard]] static std::unique_ptr<WindowManager> CreateWindow(const std::string &window_name,
                                                                     int32_t width = 300, int32_t height = 300);
    [[nodiscard]] bool ShouldClose();
    void StartFrame();
    void EndFrame();
    void Terminate();
    [[nodiscard]] inline int32_t GetWindowWidth() const
    {
        return window_data_.width;
    }
    [[nodiscard]] inline int32_t GetWindowHeight() const
    {
        return window_data_.height;
    }

    [[nodiscard]] GLFWwindow *GetNativeWindowHandle() const
    {
        GL_ASSERT(window_ != nullptr, "[WindowManager::GetNativeWindowHandle] GLFW window not initialized");
        return window_;
    }

    // We set the callback that gets invoked when an invoked
    // Thus the application or whatever entity that creates the window  also has
    // control of how to process the events generated at the window level
    void SetEventCallbackFunction(std::function<void(Event &)> func);

  private:
    [[nodiscard]] bool initWindow(const std::string &window_name, int32_t width, int32_t height);
    void setGLFWEventCallbacks();

  private:
    GLFWwindow *window_ = nullptr;
    std::unique_ptr<RenderingContext> render_ctx_;
    [[maybe_unused]] std::unique_ptr<Input> input_polling_handle_instance_;
    struct WindowData
    {
        int32_t width;
        int32_t height;
        std::function<void(Event &)> event_callback_function = nullptr;
    } window_data_;
};
} // namespace glbasic
