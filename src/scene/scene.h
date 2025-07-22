#pragma once
#include <string>
#include <memory>
#include <vector>
#include "scene/gameObject.h"

class Scene
{
private:
public:
    std::vector<std::unique_ptr<GameObject>> gameObjects;

    void Update();
    template<typename... Args>
    GameObject* instantiate(Args&&... args);
};

/* # note to self : you dont know this hsit learn beter # */
template<typename... Args>
GameObject* Scene::instantiate(Args&&... args){
    auto obj = std::make_unique<GameObject>(std::forward<Args>(args)...);
    GameObject* ptr = obj.get();
    gameObjects.push_back(std::move(obj));
    // this one is optional really, but being done here.
    ptr->setupDefault();
    return ptr;
}

void Scene::Update(){
    for(auto& gameObject : gameObjects){
        for(auto& script : gameObject->scripts){
            script->OnUpdate(44.0f);
        }
    }
}