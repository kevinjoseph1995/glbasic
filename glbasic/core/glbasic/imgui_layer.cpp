//
// Created by kevin on 7/6/21.
//

#include "imgui/imgui_layer.h"
#include "events/event.h"
#include "spdlog/spdlog.h"

namespace glbasic
{
void ImguiLayer::OnAttach()
{
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(Application::GetApplicationInstance().GetWindowManager()->GetNativeWindowHandle(),
                                 true);
    ImGui_ImplOpenGL3_Init("#version 400");
}
void ImguiLayer::OnDetach()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
}

void ImguiLayer::OnEvent(glbasic::Event &e)
{
    spdlog::debug("[ImguiLayer::OnEvent] Event name: {0}", e.GetNameString());
    if (block_events_)
    {
        ImGuiIO &io = ImGui::GetIO();
        bool handled = false;
        handled |= e.IsInCategory(MouseEvent) & io.WantCaptureMouse;
        handled |= e.IsInCategory(KeyboardEvent) & io.WantCaptureKeyboard;
        e.SetEventHandled(handled);
    }
}
void ImguiLayer::Update()
{
    begin();
    if (imgui_render_func)
    {
        imgui_render_func();
    }
    end();
}
void ImguiLayer::begin()
{
    ImGuiIO &io = ImGui::GetIO();
    glbasic::Application &app = glbasic::Application::GetApplicationInstance();
    io.DisplaySize = ImVec2((float)app.GetWindowWidth(), (float)app.GetWindowHeight());
    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
}
void ImguiLayer::end()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    // ImGui::UpdatePlatformWindows(); TODO: Enable with docking
}
} // namespace glbasic