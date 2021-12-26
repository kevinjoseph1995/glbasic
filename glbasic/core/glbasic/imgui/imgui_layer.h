#pragma once

#include "../application.h"
#include "../events/event.h"
#include "../events/key_event.h"
#include "../events/mouse_event.h"
#include "../events/window_event.h"
#include "../layer.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <utility>

namespace glbasic
{
class ImguiLayer : public Layer
{
  public:
    explicit ImguiLayer(const std::string &layer_name, bool block_events = true)
        : Layer(layer_name), block_events_(block_events)
    {
    }

    void OnEvent(Event &e) final;
    void OnAttach() final;
    void OnDetach() final;
    void Update() final;
    void SetImguiRenderFunction(std::function<void()> f)
    {
        imgui_render_func = std::move(f);
    }

  private:
    static void begin();
    static void end();
    std::function<void()> imgui_render_func;
    bool block_events_ = true;
};
} // namespace glbasic
