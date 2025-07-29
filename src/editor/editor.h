#pragma once
#include "input/inputManager.h"
#include "core/engineContext.h"
#include "scene/transform.h"
#include "editor/editorUI.h"
#include "core/platform.h"

///// ***TEMP***
#include "blockMove.h"

class Editor
{
private:
    InputManager* inputManager;
    Platform* platform;
    Camera editorCamera;
    public:
    void processInput(float deltaTime);
    bool init(GLFWwindow* window);
    Camera* getCamera();
    float lastX = 400;
    float lastY = 300;
    bool runningGame;
    EditorUI editorUI;
};

void mouseInput(GLFWwindow* window, double xpos, double ypos){
    Editor* editor = static_cast<Editor*>(glfwGetWindowUserPointer(window));
    if(!editor) return;
    
    float xoffset = xpos - editor->lastX;
    float yoffset = editor->lastY - ypos;
    editor->lastX = xpos;
    editor->lastY = ypos;
    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    Camera* tempCam = editor->getCamera();

    
    tempCam->transform.rotation.x += yoffset;
    tempCam->transform.rotation.y += xoffset;
    if(tempCam->transform.rotation.x<-89.0f) tempCam->transform.rotation.x = -89.0f;
    if(tempCam->transform.rotation.x>89.0f)  tempCam->transform.rotation.x = 89.0f;
}

bool Editor::init(GLFWwindow* window){
    runningGame = false;
    inputManager = gEngineContext->inputManager;
    platform = gEngineContext->platform;
    editorCamera.transform.setPosition({0.0f, 0.0f, 5.0f});
    editorCamera.transform.setRotation({0.0f, -90.0f, 0.0f});
    glfwSetWindowUserPointer(platform->getWindow(), this);
    platform->setMouseCallback(mouseInput);
    editorUI.init(window);
    return 1;
}

void Editor::processInput(float deltaTime){
    if(runningGame){
        if(inputManager->isKeyJustReleased(GLFW_KEY_P)) runningGame = !runningGame;
        return;
    }

    // calculate deltaTime first
    float camSpeed = 2.0f * deltaTime;
    if(inputManager->isKeyPressed(GLFW_KEY_LEFT_CONTROL)) camSpeed*=2.0f;
    
    if(inputManager->isKeyPressed(GLFW_KEY_ESCAPE)) platform->shutdown();
    if(inputManager->isKeyPressed(GLFW_KEY_BACKSPACE)) platform->changeCursorVisibility();
    if(inputManager->isKeyPressed(GLFW_KEY_W)) editorCamera.transform.movePosition(editorCamera.cameraFront * camSpeed);
    if(inputManager->isKeyPressed(GLFW_KEY_S)) editorCamera.transform.movePosition(editorCamera.cameraFront * -camSpeed);
    if(inputManager->isKeyPressed(GLFW_KEY_A)) editorCamera.transform.movePosition(glm::normalize(glm::cross(editorCamera.cameraFront, editorCamera.cameraUp)) * -camSpeed);
    if(inputManager->isKeyPressed(GLFW_KEY_D)) editorCamera.transform.movePosition(glm::normalize(glm::cross(editorCamera.cameraFront, editorCamera.cameraUp)) * camSpeed);
    if(inputManager->isKeyPressed(GLFW_KEY_LEFT_SHIFT)) editorCamera.transform.movePosition(glm::vec3(0.0f, -1.0f, 0.0f) * deltaTime);
    if(inputManager->isKeyPressed(GLFW_KEY_SPACE)) editorCamera.transform.movePosition(glm::vec3(0.0f, 1.0f, 0.0f) * deltaTime);

    if(inputManager->isKeyPressed(GLFW_KEY_UP)) editorCamera.transform.moveRotation({0.02f, 0.0f, 0.0f});
    if(inputManager->isKeyPressed(GLFW_KEY_DOWN)) editorCamera.transform.moveRotation({-0.02f, 0.0f, 0.0f});
    if(inputManager->isKeyPressed(GLFW_KEY_RIGHT)) editorCamera.transform.moveRotation({0.0f, 0.02f, 0.0f});
    if(inputManager->isKeyPressed(GLFW_KEY_LEFT)) editorCamera.transform.moveRotation({0.0f, -0.02f, 0.0f});
    
    // ***TEMP*** this acts as a placeholder for future gameobject creation UI
    if(inputManager->isKeyPressed(GLFW_KEY_I)){
        if(gEngineContext->activeScene->gameObjects.size() < 1){
            GameObject* gm = gEngineContext->activeScene->instantiate();
            gm->addScript<BlockMove>();
        }
    }
    if(inputManager->isKeyJustReleased(GLFW_KEY_P)) runningGame = !runningGame;
    
}

Camera* Editor::getCamera(){
    return &editorCamera;
}