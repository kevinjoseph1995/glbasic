//
// Created by kevin on 7/6/21.
//
#include "glbasic/application.h"
#include "glbasic/gl_debug.h"

#include "glbasic/renderer/renderer.h"
#include "spdlog/cfg/env.h"
#include "spdlog/spdlog.h"

namespace glbasic
{

Application *Application::application_ptr_ = nullptr;

Application::Application(const std::string &application_name, int32_t window_width, int32_t window_height)
{
    GL_ASSERT(application_ptr_ == nullptr, "[Application::Application]Trying to create multiple application instances");
    application_ptr_ = this;
    window_ = glbasic::WindowManager::CreateWindow(application_name, window_width, window_height);
    GL_ASSERT(window_, "Failed to create window");
    window_->SetEventCallbackFunction([this](glbasic::Event &event) { this->OnEvent(event); });
    spdlog::cfg::load_env_levels();
    glbasic::Renderer::Init();
}

void Application::Run()
{
    while (!should_close_)
    {
        window_->StartFrame();
        // Computing how long each frame took
        const auto time_now = std::chrono::steady_clock::now();
        const auto delta_time = time_now - last_call_time_;
        last_call_time_ = time_now;
        spdlog::trace("[Application::Run] Frame took {0}ms",
                      std::chrono::duration_cast<std::chrono::milliseconds>(delta_time).count());
        update(std::chrono::duration_cast<std::chrono::microseconds>(delta_time).count());
        window_->EndFrame();
    }
}

} // namespace glbasic