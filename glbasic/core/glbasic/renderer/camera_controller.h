//
// Created by kevin on 8/15/21.
//

#ifndef GL_BASIC_CAMERA_CONTROLLER_H
#define GL_BASIC_CAMERA_CONTROLLER_H

#include "glbasic/events/key_event.h"
#include "glbasic/events/mouse_event.h"
#include "glbasic/events/window_event.h"
#include "glbasic/renderer/camera.h"

#include "spdlog/spdlog.h"
#include <memory>

namespace glbasic
{
class CameraController
{
  public:
    void SetCamera(std::unique_ptr<Camera> camera, const glm::vec4 &viewport);
    [[nodiscard]] inline Camera *GetCamera() const
    {
        if (camera_)
        {
            return camera_.get();
        }
        else
        {
            spdlog::error("[CameraController::GetCamera] Camera not set");
            return nullptr;
        }
    }
    void OnUpdate(long delta_time_us);
    [[nodiscard]] bool OnEvent(Event &event);

  private:
    std::unique_ptr<Camera> camera_ = nullptr;
};
} // namespace glbasic

#endif // GL_BASIC_CAMERA_CONTROLLER_H
