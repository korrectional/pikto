#pragma once
#include <string>
#include <memory>
#include <vector>
#include "scene/gameObject.h"
#include "graphics/camera.h"

class Scene
{
private:
public:
    std::vector<std::unique_ptr<GameObject>> gameObjects;
    Camera sceneCamera; 

    void Update(float deltaTime);
    void Start();
    template<typename... Args>
    GameObject* instantiate(Args&&... args);
    Camera* getCamera();
};

/* # note to self : you dont know this hsit learn beter # */
template<typename... Args>
GameObject* Scene::instantiate(Args&&... args){
    auto obj = std::make_unique<GameObject>(std::forward<Args>(args)...);
    GameObject* ptr = obj.get();
    gameObjects.push_back(std::move(obj));
    // this one is optional really, but being done here.
    ptr->setupDefault();
    ptr->name = "GO"+std::to_string(gameObjects.size());
    return ptr;
}

void Scene::Update(float deltaTime){
    for(auto& gameObject : gameObjects){
        for(auto& script : gameObject->scripts){
            script->OnUpdate(deltaTime);
        }
    }
}

void Scene::Start(){
    
    for(int i = gameObjects.size() - 1; i >= 0; i--){
        if(gameObjects[i]->scripts.empty()) continue;
        for(int j = gameObjects[i]->scripts.size() - 1; j >= 0; j--){
            gameObjects[i]->scripts[j]->OnCreate();
        }
    }
    std::cout<<"Finished starting the scene\n";
}

Camera* Scene::getCamera(){
    return &sceneCamera;
}