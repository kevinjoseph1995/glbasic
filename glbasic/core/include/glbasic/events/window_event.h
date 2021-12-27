//
// Created by kevin on 7/5/21.
//
#pragma once

#include "glbasic/events/event.h"
namespace glbasic
{
class WindowResizeEvent : public glbasic::Event
{
  public:
    WindowResizeEvent(const int32_t window_width, const int32_t window_height)
        : window_width_(window_width), window_height_(window_height)
    {
    }
    EVENT_CLASS_TYPE(WindowResizeEvent);
    EVENT_CATEGORY_TYPE(WindowEvent);
    [[nodiscard]] inline int32_t GetWindowWidth() const
    {
        return window_width_;
    }
    [[nodiscard]] inline int32_t GetWindowHeight() const
    {
        return window_height_;
    }
    WindowResizeEvent() = delete;

  private:
    int32_t window_width_, window_height_;
};

class WindowCloseEvent : public glbasic::Event
{
  public:
    EVENT_CLASS_TYPE(WindowCloseEvent);
    EVENT_CATEGORY_TYPE(WindowEvent);
};

} // namespace glbasic