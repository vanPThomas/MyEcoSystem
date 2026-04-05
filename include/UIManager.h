#pragma once
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include <cstring>
#include <cctype>
#include "Creature.h"

class UIManager
{
public:
    UIManager();
    ~UIManager();

    GLFWwindow* window = nullptr;
    ImGuiIO* io = nullptr;

    int simulationScreenWidth = 1000;
    int simulationScreenHeight = 1000;

    bool render();
private:
    void renderSimulationScreen();
};