#pragma once
#include <unordered_map>
#include "core/platform.h"

class InputManager
{
private:
    Platform* platform;
public:
    std::unordered_map<int, bool> currentKeys;
    std::unordered_map<int, bool> lastKeys;


    InputManager(Platform* platform) : platform(platform) {};
    bool isKeyPressed(int key);
    bool isKeyJustReleased(int key);
    void update();
};

// Check if key is being pressed. Use GLFW_KEY_[keyname]. Example: isKeyPressed(GLFW_KEY_ESCAPE);
bool InputManager::isKeyPressed(int key){
    return currentKeys[key];
}

// Check if key was just released. Use GLFW_KEY_[keyname]. Example: isKeyReleased(GLFW_KEY_ESCAPE);
bool InputManager::isKeyJustReleased(int key){
    return !currentKeys[key] && lastKeys[key];
}

void InputManager::update(){
    lastKeys = currentKeys;
    for (int i = GLFW_KEY_SPACE; i < GLFW_KEY_LAST; i++)
    {
        currentKeys[i] = platform->isKeyPressed(i);
    }
    
}