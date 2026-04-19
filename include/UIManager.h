#pragma once
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include <cstring>
#include <cctype>
#include "Creature.h"
#include <cstdlib>   // for rand()
#include <ctime>     // for time()
#include <vector>

class UIManager
{
public:
    UIManager();
    ~UIManager();

    GLFWwindow* window = nullptr;
    ImGuiIO* io = nullptr;

    // Creature testCreature;
    ImVector<Creature> creatures;

    void SpawnRandomCreature();

    int simulationScreenWidth = 1000;
    int simulationScreenHeight = 1000;

    bool render();
private:
    void renderSimulationScreen();
    void renderDataInspector();

    void handleCreatureSelection();

    int selectedCreatureIndex = -1;

    // === deltaTime ===
    double lastTime = 0.0;
    float  deltaTime = 0.0f;
};