#pragma once
#include "core/platform.h"
#include "graphics/renderer.h"
#include "input/inputManager.h"
#include "scene/scene.h"

class EngineContext
{
public:
    Platform* platform;
    InputManager* inputManager;
    Renderer* renderer;
    Scene* activeScene;
};

inline EngineContext* gEngineContext = nullptr;