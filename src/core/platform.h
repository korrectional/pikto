#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "graphics/screenSize.h"

class Platform
{
private:
    GLFWwindow* window;
    float lastFrame;
    float currentFrame;
public:
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    bool shouldClose();
    void shutdown();
    int initWindow();
    void update();
    GLFWwindow* getWindow();
    bool isKeyPressed(int key);
    void setMouseCallback(void (*func)(GLFWwindow* window, double xpos, double ypos));
    void disableCursor();
    void enableCursor();
    float getTime();
    float deltaTime = 0.0f;
};
//GLFWwindow* window, double xpos, double ypos
void Platform::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

bool Platform::shouldClose()
{
    return glfwWindowShouldClose(window);
}

void Platform::shutdown(){
    glfwTerminate();
    std::exit(0);
}

int Platform::initWindow()
{
    // set glfw parameters
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // create window
    window = glfwCreateWindow(WIDTH, HEIGHT, "Pick2", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, Platform::framebufferSizeCallback); // this function is called when window resized
    disableCursor();
    // init glad
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {std::cout<<"Failed to init GLAD\n"; return -1;}
    return 1;
}

void Platform::disableCursor(){
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
void Platform::enableCursor(){
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Platform::update(){
    currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    glfwSwapBuffers(window);
    glfwPollEvents();
}

GLFWwindow* Platform::getWindow(){
    return window;
}

bool Platform::isKeyPressed(int key){
    return glfwGetKey(window, key) == GLFW_PRESS;
}

void Platform::setMouseCallback(void (*callbackFunction)(GLFWwindow* window, double xpos, double ypos)){
    glfwSetCursorPosCallback(window, callbackFunction);
}

float Platform::getTime(){
    return glfwGetTime();
}