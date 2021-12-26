#include "glbasic/glbasic.h"
#include "glbasic/objects/cube.h"
#include "glbasic/file_utils.h"
#include <experimental/filesystem>
#include <spdlog/spdlog.h>

class CubeDemo : public glbasic::Application
{
  public:
    bool Initialize(const std::string &application_name, int32_t window_width, int32_t window_height) override
    {
        if (!initializeWindow(application_name, window_width, window_height))
        {
            return false;
        }

        // Setup camera
        camera_controller_.SetCamera(std::make_unique<glbasic::PerspectiveCamera>(
                                         45.0f, float(window_width) / float(window_height), 0.1f, 10.0f),
                                     {0, 0, float(window_width), float(window_height)});

        camera_controller_.GetCamera()->LookAt({0.0f, 0.0f, 5.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f});

        if (!cube_.Initialize(glm::mat4(1.0f), 2.0f, {100, 0, 0, 1}))
        {
            spdlog::error("Failed to initialize glbasic cube object");
            return false;
        }

        return true;
    }

    void OnEvent(glbasic::Event &e) override
    {
        glbasic::EventDispatcher dispatcher(e);
        dispatcher.Dispatch<glbasic::WindowResizeEvent>([&](const glbasic::WindowResizeEvent &e) -> bool {
            glbasic::Renderer::OnWindowResize(e.GetWindowWidth(), e.GetWindowHeight());
            return false;
        });

        dispatcher.Dispatch<glbasic::WindowCloseEvent>([&](const glbasic::WindowCloseEvent &e) -> bool {
            if (should_close_)
            {
                return false;
            }
            should_close_ = true;
            return true;
        });
        dispatcher.Dispatch<glbasic::KeyPressedEvent>([&](const glbasic::KeyPressedEvent &e) -> bool {
            if (e.GetKeyCode() == GLBASIC_KEY_ESCAPE)
            {
                should_close_ = true;
            }
            return true;
        });
        auto event_handled = camera_controller_.OnEvent(e);
    }

  private:
    void update(const long delta_time_us) override
    {
        glbasic::Renderer::BeginScene(*(camera_controller_.GetCamera()));
        camera_controller_.OnUpdate(delta_time_us);
        glbasic::Renderer::Submit(cube_.GetShader(), cube_.GetVAO());
        glbasic::Renderer::EndScene();
    }

  private:
    glbasic::Cube cube_;
    glbasic::CameraController camera_controller_;
};