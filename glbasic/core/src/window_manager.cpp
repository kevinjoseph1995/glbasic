#include "glbasic/window_manager.h"

// clang-format off
//#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on
#include <utility>

#include "glbasic/events/key_event.h"
#include "glbasic/events/mouse_event.h"
#include "glbasic/events/window_event.h"
#include "glbasic/gl_debug.h"
#include "glbasic/renderer/render_command.h"
#include "glbasic/renderer/rendering_context.h"
#include <spdlog/cfg/env.h>
#include <spdlog/spdlog.h>

using namespace glbasic;

bool WindowManager::initWindow(const std::string &window_name, const int32_t width, const int32_t height)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window_ = glfwCreateWindow(width, height, window_name.c_str(), nullptr, nullptr);
    if (window_ == nullptr)
    {
        spdlog::critical("[WindowManager::initWindow]Failed to create GLFW Window");
        glfwTerminate();
        return false;
    }
    render_ctx_ = glbasic::RenderingContext::Create();
    render_ctx_->Init(window_);

    window_data_.width = width;
    window_data_.height = height;

    // Set pointer to user data that can then be accessed via glfwGetWindowUserPointer
    glfwSetWindowUserPointer(window_, &window_data_);
    // Set the GLFW event callbacks
    setGLFWEventCallbacks();

    input_polling_handle_instance_ = std::make_unique<Input>();

    return true;
}

bool WindowManager::ShouldClose()
{
    GL_ASSERT(window_ != nullptr, "[WindowManager::ShouldClose]");
    return glfwWindowShouldClose(window_);
}

void WindowManager::StartFrame()
{
    GL_ASSERT(window_ != nullptr, "[WindowManager::StartFrame]");
    RenderCommand::Clear();
}

void WindowManager::EndFrame()
{
    GL_ASSERT(window_ != nullptr, "[WindowManager::EndFrame]");
    render_ctx_->SwapBuffers();
    glfwPollEvents();
}

void WindowManager::Terminate()
{
    GL_ASSERT(window_ != nullptr, "[WindowManager::Terminate]");
    glfwDestroyWindow(window_);
    glfwTerminate();
    window_ = nullptr;
}

std::unique_ptr<WindowManager> WindowManager::CreateWindow(const std::string &window_name, const int32_t width,
                                                           const int32_t height)
{
    static bool window_previously_created = false;
    static bool glfw_initialized = false;
    if (window_previously_created)
    {
        spdlog::error("[WindowManager::CreateWindow] Multiple windows not supported for now");
        return nullptr;
    }
    if (!glfw_initialized)
    {
        spdlog::info("[WindowManager::CreateWindow] GLFW initialized");
        spdlog::cfg::load_env_levels();
        // GLFW Setup
        glfwInit();
        glfw_initialized = true;
    }
    auto window = std::make_unique<WindowManager>();
    if (!window->initWindow(window_name, width, height))
    {
        spdlog::error("[WindowManager::CreateWindow] Failed to create window");
        return nullptr;
    }
    window_previously_created = true;
    return window;
}
void WindowManager::setGLFWEventCallbacks()
{
    GL_ASSERT(window_ != nullptr, "[WindowManager::setEventCallbacks]Window not initialized");
    glfwSetWindowSizeCallback(window_, [](GLFWwindow *window, const int new_width, const int new_height) {
        WindowData &window_data = *(WindowData *)glfwGetWindowUserPointer(window);
        window_data.width = new_width;
        window_data.height = new_height;
        WindowResizeEvent event(new_width, new_height);
        window_data.event_callback_function(event);
    });

    glfwSetWindowCloseCallback(window_, [](GLFWwindow *window) {
        WindowData &window_data = *(WindowData *)glfwGetWindowUserPointer(window);
        WindowCloseEvent event;
        window_data.event_callback_function(event);
    });

    glfwSetMouseButtonCallback(window_, [](GLFWwindow *window, int button, int action, int mods) {
        WindowData &window_data = *(WindowData *)glfwGetWindowUserPointer(window);
        MouseButtonEvent event(button, action, mods);
        window_data.event_callback_function(event);
    });

    glfwSetCursorPosCallback(window_, [](GLFWwindow *window, double x, double y) {
        WindowData &window_data = *(WindowData *)glfwGetWindowUserPointer(window);
        MouseMovedEvent event((float)x, (float)y);
        window_data.event_callback_function(event);
    });

    glfwSetScrollCallback(window_, [](GLFWwindow *window, double xOffset, double yOffset) {
        WindowData &window_data = *(WindowData *)glfwGetWindowUserPointer(window);
        MouseScrolledEvent event((float)xOffset, (float)yOffset);
        window_data.event_callback_function(event);
    });

    glfwSetKeyCallback(window_, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
        WindowData &window_data = *(WindowData *)glfwGetWindowUserPointer(window);
        (void)scancode;
        (void)mods;
        switch (action)
        {
        case GLFW_PRESS: {
            KeyPressedEvent event(key, 0);
            window_data.event_callback_function(event);
            break;
        }
        case GLFW_RELEASE: {
            KeyReleasedEvent event(key);
            window_data.event_callback_function(event);
            break;
        }
        case GLFW_REPEAT: {
            KeyPressedEvent event(key, 1);
            window_data.event_callback_function(event);
            break;
        }
        default: {
            GL_ASSERT(true, "[WindowManager::setGLFWEventCallbacks] invalid key action");
        }
        }
    });

    glfwSetCharCallback(window_, [](GLFWwindow *window, unsigned int keycode) {
        WindowData &window_data = *(WindowData *)glfwGetWindowUserPointer(window);
        KeyTypedEvent event(keycode);
        window_data.event_callback_function(event);
    });
}
void WindowManager::SetEventCallbackFunction(std::function<void(Event &)> func)
{
    GL_ASSERT(window_ != nullptr, "[ WindowManager::SetEventCallbackFunction]Window not initialized");
    window_data_.event_callback_function = std::move(func);
}
