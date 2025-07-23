#pragma once
#include "core/engineContext.h"
#include <iostream>

class BlockMove : public Script {
public:
    EngineContext* engine = gEngineContext;
    GameObject* second;

    void OnCreate() override {
        engine->activeScene->getCamera()->transform.setPosition({0.0f, 0.0f, 5.0f});
        engine->activeScene->getCamera()->transform.setRotation({0.0f, -90.0f, 0.0f});
        
        second =  engine->activeScene->instantiate();
    }
    void OnUpdate(float deltaTime) override {
        second->transform.movePosition({0.0f, 1.0f * deltaTime, 0.0f});
    }
};