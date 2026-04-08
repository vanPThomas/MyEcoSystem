#include "imgui.h"
#include "UIManager.h"

UIManager::UIManager()
{
    // GLFW Window Hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    if (!glfwInit())
    {
        std::cerr << "Failed to init GLFW\n";
        return;
    }

    window = glfwCreateWindow(1920, 1080, "Ecosystem Simulator", NULL, NULL);  
    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // vsync

    // ImGui setup
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO();

    // io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    ImGui::GetIO().FontGlobalScale = 1.0f;

    // Seed random number generator once (at startup)
    srand(static_cast<unsigned int>(time(nullptr)));

    // Spawn the creature at a random position inside the simulation area
    for (int i = 0; i < 10; i++)
    {
        SpawnRandomCreature();
    }
}

UIManager::~UIManager()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool UIManager::render()
{
    if (!window || glfwWindowShouldClose(window))
        return false;

    glfwPollEvents();

    // Start a new ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    renderSimulationScreen();
    renderDataInspector();
    
    // Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.12f, 0.12f, 0.13f, 1.0f);   // Dark background
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
    return true;
}

// ====================== SIMULATION WINDOW ======================
void UIManager::renderSimulationScreen()
{
    ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(simulationScreenWidth, simulationScreenHeight), ImGuiCond_FirstUseEver);

    ImGui::Begin("Simulation Window");

    // Get the top-left corner of the window's content area
    ImVec2 origin = ImGui::GetCursorScreenPos();

    // Use the stored creatures
    for (auto c: creatures)
    {
        ImVec2 pos = ImVec2(
            origin.x + c.x,
            origin.y + c.y
        );
        ImDrawList* drawList = ImGui::GetWindowDrawList();
    
        drawList->AddCircleFilled(
            pos,
            15.0f,
            IM_COL32(255, 100, 180, 255)
        );
    }


    ImGui::End();
}

// ====================== NEW: DATA INSPECTOR ======================
void UIManager::renderDataInspector()
{
    ImGui::Begin("Creature Inspector");

    if (selectedCreatureIndex < 0 || selectedCreatureIndex >= (int)creatures.size())
    {
        ImGui::Text("No creature selected.");
        ImGui::Text("Click on a creature in the Simulation Window to inspect it.");
    }
    else
    {
        Creature& selected = creatures[selectedCreatureIndex];

        ImGui::Text("Creature #%d", selectedCreatureIndex);
        ImGui::Separator();

        // === DNA Section ===
        if (ImGui::CollapsingHeader("DNA", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Text("Speed:         %.1f", selected.dna.speed);
            ImGui::Text("Vision Range:  %.1f", selected.dna.visionRange);
            ImGui::Text("Size:          %.1f", selected.dna.size);
            ImGui::Text("Strength:      %.1f", selected.dna.strength);
            ImGui::Text("Is Male:       %s", selected.dna.isMale ? "Yes" : "No");
            ImGui::Text("Metabolism:    %.2f", selected.dna.metabolism);
            ImGui::Text("Aggression:    %.2f", selected.dna.aggression);
            ImGui::Text("Mutation Rate: %.3f", selected.dna.mutationRate);
            // Add more DNA fields as you like
        }

        ImGui::Separator();

        // === Brain Section ===
        if (ImGui::CollapsingHeader("Brain", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Text("State:         %s", 
                selected.brain.currentState == Brain::State::Wandering ? "Wandering" :
                selected.brain.currentState == Brain::State::SeekingFood ? "Seeking Food" : "Other");

            ImGui::Text("Hunger:        %.2f", selected.brain.hunger);
            ImGui::Text("Fear:          %.2f", selected.brain.fear);
            ImGui::Text("Tiredness:     %.2f", selected.brain.tiredness);
            ImGui::Text("Mating Drive:  %.2f", selected.brain.matingDrive);
            ImGui::Text("Anger:         %.2f", selected.brain.anger);
        }
    }

    ImGui::End();
}

// ====================== SPAWN ======================
void UIManager::SpawnRandomCreature()
{
    float randomX = static_cast<float>(rand() % simulationScreenWidth);
    float randomY = static_cast<float>(rand() % simulationScreenHeight);

    Creature newCreature(randomX, randomY);
    creatures.push_back(newCreature);
}