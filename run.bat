@echo off

g++ src/main/main.cpp thirdparty/glad/include/glad/glad.c -Ithirdparty/glad/include -Isrc -Ithirdparty -Ithirdparty/glfw/include -Lthirdparty/glfw/lib -lglfw3 -lopengl32 -lgdi32 -o build/pick2.exe
.\build\pick2.exe