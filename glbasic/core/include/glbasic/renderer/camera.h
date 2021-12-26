#pragma once

#include <glm/glm.hpp>

namespace glbasic
{

class Camera
{
  public:
    [[nodiscard]] inline const glm::mat4 &GetProjectionMatrix() const
    {
        return projection_;
    }
    [[nodiscard]] inline const glm::mat4 &GetViewMatrix() const
    {
        return view_;
    }

    [[nodiscard]] inline const glm::mat4 &GetViewProjectionMatrix() const
    {
        return view_projection_;
    }

    [[nodiscard]] inline const glm::vec3 &GetEyePosition() const
    {
        return eye_;
    }
    [[nodiscard]] inline const glm::vec3 &GetUpDirection() const
    {
        return up_;
    }
    [[nodiscard]] inline const glm::vec3 &GetTargetPosition() const
    {
        return target_;
    }
    inline void LookAt(const glm::vec3 &eye, const glm::vec3 &up, const glm::vec3 &target)
    {
        eye_ = eye;
        up_ = up;
        target_ = target;
        reCalculateViewMatrix();
    }

  protected:
    void reCalculateViewMatrix();

  protected:
    // Parameters describing position and orientation of the camera is w.r.t some global reference frame
    glm::vec3 eye_ = {0.0, 0.0, 0.0};    // Position of the camera w.r.t to world
    glm::vec3 up_ = {0.0, 1.0, 0.0};     // Vector denoting up direction
    glm::vec3 target_ = {0.0, 0.0, 1.0}; // The target the camera is looking at

    glm::mat4 projection_ = glm::mat4(1);
    glm::mat4 view_projection_ = glm::mat4(1);
    glm::mat4 view_ = glm::mat4(1); // Camera Transformation Matrix. Transforms World -> Camera
};

class OrthographicCamera : public Camera
{
  public:
    OrthographicCamera() = default;
    OrthographicCamera(float left, float right, float bottom, float top, float near = -1.0f, float far = 1.0);
    void SetProjection(float left, float right, float bottom, float top, float near = -1.0f, float far = 1.0);
    void RotateAboutCameraAxis(float degrees);
};

class PerspectiveCamera : public Camera
{
  public:
    PerspectiveCamera() = default;
    PerspectiveCamera(float fov_y_degrees, float aspect, float z_near, float z_far);
    void SetProjection(float fov_y_degrees, float aspect, float z_near, float z_far);
};
} // namespace glbasic
