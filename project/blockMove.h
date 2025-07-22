#pragma once
#include "core/engineContext.h"
#include <iostream>

class BlockMove : public Script {
public:
    EngineContext* engine = gEngineContext;

    void OnCreate() override {
        std::cout<<"Created\n";
    }
    void OnUpdate(float deltaTime) override {
        std::cout<<"Updated\n";
        GameObject* first = engine->activeScene->instantiate();
        GameObject* second = engine->activeScene.instantiate();
        second->transform.setPosition({0.0f, 2.0f, 0.0f});
    }
};