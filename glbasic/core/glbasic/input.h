#pragma once

#include "glbasic/key_codes.h"

#include <glm/glm.hpp>
#include <utility>

namespace glbasic
{
class Input
{
  public:
    Input();
    inline static Input &GetInputInstance()
    {
        return *input_instance_ptr_;
    }
    [[nodiscard]] static bool IsKeyPressed(KeyCode key);
    [[nodiscard]] static bool IsMouseButtonPressed(int button);
    [[nodiscard]] static bool IsMouseButtonReleased(int button);
    [[nodiscard]] static glm::vec2 GetMousePosition();

  private:
    static Input *input_instance_ptr_;
};
} // namespace glbasic