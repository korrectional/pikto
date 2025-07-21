#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include <glad/glad.h>

// responsible for textures
class Material
{
private:
    unsigned int texture;
public:
    
    void setupDefault(); 
    void render();
};

void Material::setupDefault(){
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

}

void Material::render(){
    glBindTexture(GL_TEXTURE_2D, texture);
}