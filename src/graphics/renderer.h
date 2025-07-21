#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include <math.h>
#include "graphics/shader.h"
#include "graphics/camera.h"
#include "graphics/screenSize.h"
#include "scene/scene.h"
#include "scene/gameObject.h"


class Renderer
{
private:
    int modelLoc;
    int viewLoc;
    int projectionLoc;
    Shader* shaderProgram = nullptr; // Use pointer, initialize later
    unsigned int texture;

public:
    Renderer() {} // Remove shaderProgram construction here
    int init();
    void renderScene(Scene* scene, Camera* camera);
};

int Renderer::init(){
    // openGL is here!
    glViewport(0, 0, WIDTH, HEIGHT);
    

    glClearColor(0.3f, 0.5f, 0.9f, 1.0f); // classic=0.4f, 0.6f, 1.0f, 1.0f
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    shaderProgram = new Shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // THIS IS WHERE THE USUAL TEXTURE STUFF USED TO HAPPEN

    // THIS IS WHERE THE USUAL ARRAY STUFF USED TO HAPPEN

    glPolygonMode(GL_FRONT_AND_BACK, (true ? GL_FILL : GL_LINE));
    glEnable(GL_DEPTH_TEST);


    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

    
    //std::cout<<"Loading Time: "<<(glfwGetTime()-loadingStartTime)<<"\n";
    modelLoc = glGetUniformLocation(shaderProgram->ID, "model");
    viewLoc = glGetUniformLocation(shaderProgram->ID, "view");
    projectionLoc = glGetUniformLocation(shaderProgram->ID, "projection");

    return 1;
}

void Renderer::renderScene(Scene* scene, Camera* camera){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderProgram->use();
    
    // # ingame # //
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), WIDTHF / HEIGHTF, 0.1f, 100.0f);
    shaderProgram->setMat4(projectionLoc, projection);
    
    //camera
    
    glm::mat4 view;
    view = camera->lookAt();
      
    shaderProgram->setMat4(viewLoc, view);


    // gameobject
    
    
    for(auto& gameObject : scene->gameObjects){
        gameObject->mesh.render();
        gameObject->material.render();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, gameObject->transform.position);
        shaderProgram->setMat4(modelLoc, model);    
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    
}