//
// Created by kevin on 8/15/21.
//

#include "camera_controller.h"
#include "glbasic/input.h"
#include "spdlog/spdlog.h"

namespace glbasic
{

void CameraController::SetCamera(std::unique_ptr<Camera> camera, const glm::vec4 &viewport)
{
    // Transfers ownership
    (void)viewport;
    camera_ = std::move(camera);
}

void CameraController::OnUpdate(const long delta_time_us)
{
    (void)delta_time_us;
}
bool CameraController::OnEvent(Event &event)
{
    (void)event;
    return false;
}
} // namespace glbasic
