//
// Created by kevin on 7/25/21.
//
#include "glbasic/renderer/camera.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"

namespace glbasic
{
void Camera::reCalculateViewMatrix()
{
    // The view matrix transforms a point in world-coordinates to camera-coordinates
    view_ = glm::lookAt(eye_, target_, up_);
    view_projection_ = projection_ * view_;
}

OrthographicCamera::OrthographicCamera(const float left, const float right, const float bottom, const float top,
                                       const float near, const float far)
{
    SetProjection(left, right, bottom, top, near, far);
}

void OrthographicCamera::SetProjection(const float left, const float right, const float bottom, const float top,
                                       const float near, const float far)
{
    projection_ = glm::ortho(left, right, bottom, top, near, far);
    reCalculateViewMatrix();
}

void OrthographicCamera::RotateAboutCameraAxis(const float degrees)
{
    const glm::vec3 axis_of_rotation = target_ - eye_;
    up_ = glm::rotate(up_, glm::radians(degrees), axis_of_rotation);
    reCalculateViewMatrix();
}

PerspectiveCamera::PerspectiveCamera(float fov_y_degrees, float aspect, float z_near, float z_far)
{
    SetProjection(fov_y_degrees, aspect, z_near, z_far);
}
void PerspectiveCamera::SetProjection(float fov_y_degrees, float aspect, float z_near, float z_far)
{
    projection_ = glm::perspective(fov_y_degrees, aspect, z_near, z_far);
}
}; // namespace glbasic