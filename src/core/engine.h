#pragma once
#include "graphics/shader.h"
#include "core/platform.h"
#include "graphics/renderer.h"
#include "input/inputManager.h"
#include "core/engineContext.h"
#include "editor/editor.h"
#include "scene/scene.h"

class Engine
{
private:
    Platform platform;
    Renderer renderer;
    InputManager inputManager;
    Editor editor;
    Scene scene;
public:
    Engine() : platform(), renderer(), inputManager(&platform) {};
    int init();
    bool update();
    void shutdown();
};

int Engine::init(){
    bool platformSuccessful = platform.initWindow();
    bool rendererSuccessful = renderer.init(); 
    
    // set gEngineContext;
    gEngineContext = new EngineContext();
    gEngineContext->inputManager = &inputManager;
    gEngineContext->renderer = &renderer;
    gEngineContext->platform = &platform;
    
    bool editorSuccessful = editor.init();

    std::cout<<platformSuccessful<<rendererSuccessful<<editorSuccessful<<"\n";
    // and thsi one is ***TEMP***
    GameObject* first = scene.instanctiate();
    GameObject* second = scene.instanctiate();
    second->transform.setPosition({0.0f, 2.0f, 0.0f});
    // and thsi one is ***TEMP***
    if(platformSuccessful && rendererSuccessful && editorSuccessful) return 1;
    return -1;
}

// returns false if should close
bool Engine::update(){
    editor.processInput();
    

    // here we will have the great cookie of the scripts
    
    
    renderer.renderScene(&scene, editor.getCamera());
    platform.update();
    return !platform.shouldClose();
}

void Engine::shutdown(){
    platform.shutdown();
}