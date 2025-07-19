#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "scene/transform.h"

class Camera
{
private:
public:
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::mat4 lookAt();
    Transform transform;
};

glm::mat4 Camera::lookAt(){
    cameraFront = glm::normalize(glm::vec3(
        cos(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.x)),
        sin(glm::radians(transform.rotation.x)),
        sin(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.x))
    ));
    return glm::lookAt(transform.position, transform.position + cameraFront, cameraUp);
}