#pragma once
#include <string>
#include <vector>
#include <memory>
#include "scene/transform.h"
#include "graphics/mesh.h"
#include "graphics/material.h"
#include "core/script.h"

class GameObject
{
private:
    
public:
    std::string name = "default";
    Transform transform;
    Mesh mesh;
    Material material;

    // vector of scripts to be executed on this gameobject
    std::vector<std::unique_ptr<Script>> scripts;

    template<typename T, typename... Args>
    T* addScript(Args&&... args);
    void setupDefault();
};

template<typename T, typename... Args>
T* GameObject::addScript(Args&&... args) {
    auto script = std::make_unique<T>(std::forward<Args>(args)...);
    T* ptr = script.get();
    scripts.push_back(std::move(script));
    return ptr;
}

void GameObject::setupDefault(){
    mesh.setupDefault();
    material.setupDefault();
}