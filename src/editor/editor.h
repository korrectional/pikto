#pragma once
#include "input/inputManager.h"
#include "core/engineContext.h"
#include "scene/transform.h"

class Editor
{
private:
    InputManager* inputManager;
    Platform* platform;
    Camera editorCamera;
    
    float deltaTime; // difference of time between current and last frame
    float lastFrame;
    float currentFrame;
public:
    void processInput();
    bool init();
    Camera* getCamera();
    float lastX = 400;
    float lastY = 300;    
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

bool Editor::init(){
    inputManager = gEngineContext->inputManager;
    platform = gEngineContext->platform;
    editorCamera.transform.setPosition({0.0f, 0.0f, 5.0f});
    editorCamera.transform.setRotation({0.0f, -90.0f, 0.0f});
    glfwSetWindowUserPointer(platform->getWindow(), this);
    platform->setMouseCallback(mouseInput);
    return 1;
}

void Editor::processInput(){
    // calculate deltaTime first
    currentFrame = platform->getTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    float camSpeed = 2.0f * deltaTime;
    if(inputManager->isKeyPressed(GLFW_KEY_LEFT_CONTROL)) camSpeed*=2.0f;
    
    if(inputManager->isKeyPressed(GLFW_KEY_ESCAPE)) platform->shutdown();
    if(inputManager->isKeyPressed(GLFW_KEY_BACKSPACE)) platform->enableCursor();
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

}

Camera* Editor::getCamera(){
    return &editorCamera;
}