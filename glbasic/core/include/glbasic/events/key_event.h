#pragma once
#include "event.h"

namespace glbasic
{
class KeyEvent : public Event
{
  public:
    [[nodiscard]] int GetKeyCode() const
    {
        return key_code_;
    }

    EVENT_CATEGORY_TYPE(KeyboardEvent);

  protected:
    explicit KeyEvent(const int keycode) : key_code_(keycode)
    {
    }

    int key_code_;
};

class KeyPressedEvent : public KeyEvent
{
  public:
    KeyPressedEvent(const int keycode, const uint16_t repeatCount) : KeyEvent(keycode), repeat_count_(repeatCount)
    {
    }

    [[nodiscard]] uint16_t GetRepeatCount() const
    {
        return repeat_count_;
    }

    EVENT_CLASS_TYPE(KeyPressedEvent)
  private:
    uint16_t repeat_count_;
};

class KeyReleasedEvent : public KeyEvent
{
  public:
    explicit KeyReleasedEvent(const int keycode) : KeyEvent(keycode)
    {
    }

    EVENT_CLASS_TYPE(KeyReleasedEvent);
};

class KeyTypedEvent : public Event
{
  public:
    explicit KeyTypedEvent(const unsigned int codepoint) : codepoint_(codepoint)
    {
    }

    [[nodiscard]] inline unsigned int GetCodePoint() const
    {
        return codepoint_;
    }

    EVENT_CLASS_TYPE(KeyTypedEvent)
    EVENT_CATEGORY_TYPE(KeyboardEvent);

  private:
    unsigned int codepoint_;
};
} // namespace glbasic