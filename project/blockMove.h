#pragma once
#include "core/engineContext.h"
#include "scene/gameObject.h"
#include <iostream>

class BlockMove : public Script {
public:
    EngineContext* engine = gEngineContext;
    GameObject* second;

    void OnCreate() override {
        engine->activeScene->getCamera()->transform.setPosition({0.0f, 0.0f, 5.0f});
        engine->activeScene->getCamera()->transform.setRotation({0.0f, -90.0f, 0.0f});
        
        second =  engine->activeScene->instantiate();
        second->transform.setScale({0.4f, 0.4f, 0.4f});
    }
    void OnUpdate(float deltaTime) override {
        second->transform.movePosition({0.0f, 0.1f * deltaTime, 0.0f});
        second->transform.moveRotation({20.0f * deltaTime, 20.0f * deltaTime, 20.0f * deltaTime});
        owner->transform.moveRotation({10.0f * deltaTime, 10.0f * deltaTime, 10.0f * deltaTime});

        if(engine->inputManager->isKeyPressed(GLFW_KEY_ESCAPE)) engine->platform->shutdown();
    }
};