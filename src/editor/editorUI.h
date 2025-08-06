#pragma once
#include <iostream>
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "graphics/renderer.h"
#include "core/platform.h"
#include "core/engineContext.h"
#include "scene/gameObject.h"

class EditorUI
{
private:
    bool aboutOpen = false;
    GameObject* selectedObj = nullptr;
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
    
    ImGui::BeginMainMenuBar();
    if(ImGui::BeginMenu("Help")){
        if(ImGui::MenuItem("About")){
            aboutOpen = true;
        }
        ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
    
    if(aboutOpen){
        ImGui::Begin("About", &aboutOpen);
        ImGui::BulletText("pikto is Pick Engine's spiritual successor");
        ImGui::BulletText("it's supposed to be better written and organized\nas well as easier to use than its predecessor");
        ImGui::BulletText("Please star it on github! ");
        ImGui::SameLine(0, 0);
        ImGui::TextLinkOpenURL("https://www.github.com/korrectional/pikto/");
        ImGui::End();
    }

    ImGui::SetNextWindowPos(ImVec2(0, 8));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
    ImGui::Begin("FullscreenWindow", nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoBringToFrontOnFocus);
    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0,0), ImGuiDockNodeFlags_PassthruCentralNode);
    ImGui::End();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::SetNextWindowSize(ImVec2(WIDTH*0.6, HEIGHT*0.6));
    ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoResize);
    ImGui::Image((void*)(intptr_t)gEngineContext->renderer->textureColorbuffer, ImVec2(WIDTH*0.6, HEIGHT*0.6), ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
    ImGui::PopStyleVar(2);
    
    // gameobject list window
    ImGui::Begin("GOs");

    for(int gm = 0; gm < gEngineContext->activeScene->gameObjects.size(); gm++){
        GameObject* currentObj = gEngineContext->activeScene->gameObjects[gm].get();
        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
        if(currentObj == selectedObj){
            flags |= ImGuiTreeNodeFlags_Selected;
        }
        ImGui::TreeNodeEx((currentObj->name + "##" + std::to_string(gm /*TEMP*/)).c_str(), flags);
        if(ImGui::IsItemClicked()){
            selectedObj = currentObj;
        }

    }
    ImGui::End();
    
    // modify values of selected GO
    ImGui::Begin("Upclose");
    if(selectedObj != nullptr){
        ImGui::Text(selectedObj->name.c_str());
        ImGui::Text("X: %.2f", selectedObj->transform.position.x);
    }
    ImGui::End();
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