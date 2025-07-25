#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transform
{
public:
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 scale =    glm::vec3(1.0f, 1.0f, 1.0f);
    void setPosition(glm::vec3 position);
    void movePosition(glm::vec3 move);
    glm::mat4 getPositionMat4();
    void setRotation(glm::vec3 rotation);
    void moveRotation(glm::vec3 rotate);
    void setScale(glm::vec3 scale);
    void moveScale(glm::vec3 scale);
};

void Transform::setPosition(glm::vec3 position){
    this->position = position;
}

void Transform::movePosition(glm::vec3 move){
    this->position.x += move.x;
    this->position.y += move.y;
    this->position.z += move.z;
}

glm::mat4 Transform::getPositionMat4(){
    glm::mat4 mat = glm::mat4(1.0f);
    return glm::translate(mat, position);
}

void Transform::setRotation(glm::vec3 rotation){
    this->rotation = rotation;
}

void Transform::moveRotation(glm::vec3 rotate){
    this->rotation.x += rotate.x;
    this->rotation.y += rotate.y;
    this->rotation.z += rotate.z;
}

void Transform::setScale(glm::vec3 scale){
    this->scale = scale;
}

void Transform::moveScale(glm::vec3 scale){
    this->scale.x += scale.x;
    this->scale.y += scale.y;
    this->scale.z += scale.z;
}