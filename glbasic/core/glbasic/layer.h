#pragma once

#include <string>
#include <utility>
class Event;
namespace glbasic
{
class Layer
{
  public:
    explicit Layer(std::string layer_name) : layer_name_(std::move(layer_name))
    {
    }
    Layer() = delete;
    virtual ~Layer() = default;

    virtual void Update() = 0;
    virtual void OnEvent(Event &e) = 0;
    virtual void OnAttach() = 0;
    virtual void OnDetach() = 0;

  private:
    std::string layer_name_;
};
} // namespace glbasic
