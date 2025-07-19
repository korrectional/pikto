#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include <math.h>
#include "graphics/shader.h"
#include "graphics/camera.h"
#include "graphics/screenSize.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"


class Renderer
{
private:
    float vertices[180] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    int modelLoc;
    int viewLoc;
    int projectionLoc;
    Shader* shaderProgram = nullptr; // Use pointer, initialize later
    unsigned int VBO, VAO, texture;

public:
    Renderer() {} // Remove shaderProgram construction here
    int init();
    void renderScene(Camera* camera);
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

    // load contained texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
    glGenTextures(1, &texture);  
    glBindTexture(GL_TEXTURE_2D, texture);
    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);    
    }
    else{
        std::cout << "Failed to load texture\n";
    }
    stbi_image_free(data);

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);  
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //// color attributes
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    //glEnableVertexAttribArray(1);
    // UV coordinate
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);  



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

void Renderer::renderScene(Camera* camera){
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
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);

    glm::mat4 model = glm::mat4(1.0f);
    shaderProgram->setMat4(modelLoc, model);    
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(2.0f, 0, 0));
    shaderProgram->setMat4(modelLoc, model);    
    glDrawArrays(GL_TRIANGLES, 0, 36);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0, 0, -2.0f));
    shaderProgram->setMat4(modelLoc, model);    
    glDrawArrays(GL_TRIANGLES, 0, 36);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0, 2.0f, 0));
    shaderProgram->setMat4(modelLoc, model);    
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
}