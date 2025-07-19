#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "core/engineContext.h"
#include "core/application.h"





int main(){
    std::cout<<"Hi again\n";
    Application application;
    std::cout<<"Starting app"<<"\n";
    application.run();
    std::cout<<"DONE"<<"\n";
    return 0;
}