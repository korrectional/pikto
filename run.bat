@echo off

g++ src/main/main.cpp thirdparty/glad/include/glad/glad.c thirdparty/imgui/imgui.cpp thirdparty/imgui/imgui_draw.cpp thirdparty/imgui/imgui_tables.cpp thirdparty/imgui/imgui_widgets.cpp thirdparty/imgui/backends/imgui_impl_glfw.cpp thirdparty/imgui/backends/imgui_impl_opengl3.cpp thirdparty/imgui/misc/cpp/imgui_stdlib.cpp -Ithirdparty/glad/include -Isrc -Iproject -Ithirdparty -Ithirdparty/imgui -Ithirdparty/imgui/backends -Ithirdparty\imgui\misc\cpp -Ithirdparty/glfw/include -Lthirdparty/glfw/lib -lglfw3 -lopengl32 -lgdi32 -o build/pick2.exe
.\build\pick2.exe