#pragma once
#include "glbasic/events/event.h"
namespace glbasic
{

class MouseButtonEvent : public Event
{
  public:
    MouseButtonEvent() = delete;
    MouseButtonEvent(int button, int action, int mods) : button_(button), action_(action), mods_(mods)
    {
    }
    EVENT_CLASS_TYPE(MouseButtonEvent);
    EVENT_CATEGORY_TYPE(MouseEvent);
    [[nodiscard]] inline int GetButton() const
    {
        return button_;
    }
    [[nodiscard]] inline int GetAction() const
    {
        return action_;
    }
    [[nodiscard]] inline int GetMods() const
    {
        return mods_;
    }

  private:
    int button_, action_, mods_;
};

class MouseMovedEvent : public Event
{
  public:
    MouseMovedEvent() = delete;
    MouseMovedEvent(float x_pos, float y_pos) : x_pos_(x_pos), y_pos_(y_pos)
    {
    }
    EVENT_CLASS_TYPE(MouseMovedEvent);
    EVENT_CATEGORY_TYPE(MouseEvent);
    [[nodiscard]] inline float GetXPos() const
    {
        return x_pos_;
    }
    [[nodiscard]] inline float GetYPos() const
    {
        return y_pos_;
    }

  private:
    float x_pos_, y_pos_;
};

class MouseScrolledEvent : public Event
{
  public:
    MouseScrolledEvent() = delete;
    MouseScrolledEvent(float x_offset, float y_offset) : x_offset_(x_offset), y_offset_(y_offset)
    {
    }
    EVENT_CLASS_TYPE(MouseScrolledEvent);
    EVENT_CATEGORY_TYPE(MouseEvent);
    [[nodiscard]] inline float GetXOffset() const
    {
        return x_offset_;
    }
    [[nodiscard]] inline float GetYOffset() const
    {
        return y_offset_;
    }

  private:
    float x_offset_, y_offset_;
};

} // namespace glbasic