#pragma once
#include "core/platform.h"
#include "graphics/renderer.h"
#include "input/inputManager.h"

class EngineContext
{
public:
    Platform* platform;
    InputManager* inputManager;
    Renderer* renderer;
};

inline EngineContext* gEngineContext = nullptr;