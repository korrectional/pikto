#pragma once
#include <iostream>
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "graphics/renderer.h"
#include "core/platform.h"

class EditorUI
{
private:
    
public:
    bool init(GLFWwindow* window);
    void updateFirst();
    void updateLast();
    void shutdown();
};

bool EditorUI::init(GLFWwindow* window){
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    return 1;
}

void EditorUI::updateFirst(){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    
    if(ImGui::CollapsingHeader("Help")){
        ImGui::SeparatorText("About");
        ImGui::BulletText("pikto is Pick Engine's spiritual successor");
        ImGui::BulletText("it's supposed to be better written and organized");
        ImGui::BulletText("as well as easier to use than its predecessor");
        ImGui::BulletText("Please star it on github! ");
        ImGui::SameLine(0, 0);
        ImGui::TextLinkOpenURL("https://www.github.com/korrectional/pikto/");
    }
}

void EditorUI::updateLast(){
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void EditorUI::shutdown(){
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}