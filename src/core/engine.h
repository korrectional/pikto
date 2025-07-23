#pragma once
#include "graphics/shader.h"
#include "core/platform.h"
#include "graphics/renderer.h"
#include "input/inputManager.h"
#include "core/engineContext.h"
#include "editor/editor.h"
#include "scene/scene.h"
#include "core/script.h"

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

    int ticks = 0;
};

int Engine::init(){
    bool platformSuccessful = platform.initWindow();
    bool rendererSuccessful = renderer.init(); 
    
    // set gEngineContext;
    gEngineContext = new EngineContext();
    gEngineContext->inputManager = &inputManager;
    gEngineContext->renderer = &renderer;
    gEngineContext->platform = &platform;
    gEngineContext->activeScene = &scene;
    
    bool editorSuccessful = editor.init();

    std::cout<<platformSuccessful<<rendererSuccessful<<editorSuccessful<<"\n";
    if(platformSuccessful && rendererSuccessful && editorSuccessful) return 1;
    return -1;
}

// returns false if should close
bool Engine::update(){
    if(editor.runningGame){
        if(ticks == 0){
            scene.Start();
        }
        ticks++;
        scene.Update(platform.deltaTime);
    }
    else{
        ticks = 0;
        editor.processInput(platform.deltaTime);
    }
    
    renderer.renderScene(&scene, editor.runningGame ? scene.getCamera() : editor.getCamera());
    platform.update();
    return !platform.shouldClose();
}

void Engine::shutdown(){
    platform.shutdown();
}