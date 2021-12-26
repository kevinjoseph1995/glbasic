#pragma once
#include "glbasic/events/event.h"
#include "glbasic/gl_debug.h"
#include "glbasic/window_manager.h"

#include <chrono>
#include <memory>

namespace glbasic
{
class Application
{
  public:
    Application();
    virtual ~Application() = default;

    virtual bool Initialize(const std::string &application_name, int32_t window_width, int32_t window_height) = 0;

    void Run();
    virtual void OnEvent(Event &e) = 0;

    static inline Application &GetApplicationInstance()
    {
        return *Application::application_ptr_;
    }

    [[nodiscard]] inline int32_t GetWindowWidth() const
    {
        return window_->GetWindowWidth();
    }
    [[nodiscard]] inline int32_t GetWindowHeight() const
    {
        return window_->GetWindowHeight();
    }

    WindowManager *GetWindowManager()
    {
        GL_ASSERT(window_.get() != nullptr, "[Application::GetWindowManager] Window not initialized");
        return window_.get();
    }

  protected:
    virtual void update(long delta_time_us) = 0;

    // The window must be initialized first from the inherited Application classes Initialize function using the
    // following helper function first
    bool initializeWindow(const std::string &application_name, int32_t window_width, int32_t window_height);

  protected:
    std::unique_ptr<WindowManager> window_ = nullptr;
    bool should_close_ = false;
    std::chrono::time_point<std::chrono::steady_clock> last_call_time_{};

  private:
    static Application *application_ptr_;
};

} // namespace glbasic
