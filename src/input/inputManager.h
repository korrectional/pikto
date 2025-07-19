#pragma once
#include "core/platform.h"

class InputManager
{
private:
    Platform* platform;
public:
    InputManager(Platform* platform) : platform(platform) {};
    bool isKeyPressed(int key);
};

// Check if key is being pressed. Use GLFW_KEY_[keyname]. Example: isKeyPressed(GLFW_KEY_ESCAPE);
bool InputManager::isKeyPressed(int key){
    return platform->isKeyPressed(key);
}