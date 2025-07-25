#pragma once
class GameObject;

class Script {
public:
    GameObject* owner = nullptr;
    virtual void OnCreate() {}
    virtual void OnUpdate(float deltaTime) {}
    virtual void OnDestroy() {}
};