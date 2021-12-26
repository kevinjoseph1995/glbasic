#pragma once
#include <string>
/*
 * Event system: Heavily inspired by the Yan Chernikov's(The Cherno) game engine
 * series on YouTube
 */

#define BIT_SET(x) (1 << (x))

namespace glbasic
{

// clang-format off
enum class EventType : int32_t {   WindowResizeEvent,
                                   WindowCloseEvent,
                                   MouseButtonEvent,
                                   MouseMovedEvent,
                                   MouseScrolledEvent,
                                   KeyPressedEvent,
                                   KeyReleasedEvent,
                                   KeyTypedEvent};
// clang-format on

enum EventCategory : int32_t
{
    WindowEvent = BIT_SET(0),
    MouseEvent = BIT_SET(1),
    KeyboardEvent = BIT_SET(1)
};

#define EVENT_CLASS_TYPE(TYPE)                                                                                         \
    [[nodiscard]] static EventType GetStaticType()                                                                     \
    {                                                                                                                  \
        return EventType::TYPE;                                                                                        \
    }                                                                                                                  \
    [[nodiscard]] virtual EventType GetEventType() const override                                                      \
    {                                                                                                                  \
        return GetStaticType();                                                                                        \
    }                                                                                                                  \
    [[nodiscard]] virtual const char *GetName() const override                                                         \
    {                                                                                                                  \
        return #TYPE;                                                                                                  \
    }

#define EVENT_CATEGORY_TYPE(CATEGORY)                                                                                  \
    [[nodiscard]] virtual int32_t GetCategory() const override                                                         \
    {                                                                                                                  \
        return CATEGORY;                                                                                               \
    }

class Event
{
  public:
    [[nodiscard]] virtual EventType GetEventType() const = 0;
    [[nodiscard]] virtual int GetCategory() const = 0;
    [[nodiscard]] virtual const char *GetName() const = 0;
    [[nodiscard]] virtual std::string GetNameString() const
    {
        return GetName();
    };
    inline void SetEventHandled(bool handled)
    {
        handled_ = handled;
    }
    [[nodiscard]] inline bool Handled() const
    {
        return handled_;
    }
    [[nodiscard]] bool IsInCategory(EventCategory category) const
    {
        return GetCategory() & category;
    }

  private:
    bool handled_ = false;
};

class EventDispatcher
{
  public:
    explicit EventDispatcher(Event &event) : event_(event)
    {
    }

    template <typename T, typename F> void Dispatch(const F &func)
    {
        static_assert(std::is_base_of<Event, T>());
        if (event_.GetEventType() == T::GetStaticType())
        {
            event_.SetEventHandled(func(static_cast<T &>(event_)));
        }
    }

  private:
    Event &event_;
};

} // namespace glbasic
