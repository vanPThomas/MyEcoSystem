#pragma once
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include <cstring>
#include <cctype>

class UIManager
{
public:
    UIManager();
    ~UIManager();

    GLFWwindow* window = nullptr;
    ImGuiIO* io = nullptr;

    bool render();
private:

};