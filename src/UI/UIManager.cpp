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

// ====================== RENDER UI ======================
bool UIManager::render()
{
    if (!window || glfwWindowShouldClose(window))
        return false;

    
    // ====================== CALCULATE DELTA TIME ======================
    double currentTime = glfwGetTime();
    deltaTime = static_cast<float>(currentTime - lastTime);
    lastTime = currentTime;
    
    // Clamp deltaTime to avoid huge jumps
    if (deltaTime > 0.1f)
    deltaTime = 0.1f;

    glfwPollEvents();
    // Start ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Update all creatures with deltaTime
    for (auto& creature : creatures)
    {
        creature.update(deltaTime);
    }

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

// ====================== SIMULATION SCREEN ======================
void UIManager::renderSimulationScreen()
{
    ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(simulationScreenWidth, simulationScreenHeight), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSizeConstraints( ImVec2(simulationScreenWidth, simulationScreenHeight), ImVec2(simulationScreenWidth, simulationScreenHeight));
    ImGui::Begin("Simulation Window");

    ImVec2 origin = ImGui::GetCursorScreenPos();
    ImDrawList* drawList = ImGui::GetWindowDrawList();

    for (int i = 0; i < (int)creatures.size(); ++i)
    {
        const auto& c = creatures[i];

        ImVec2 pos(origin.x + c.getXPos(), origin.y + c.getYPos());
        float radius = c.brain.dna.getSize();

        // Choose color based on whether it's selected
        ImU32 color = (i == selectedCreatureIndex) 
            ? IM_COL32(255, 255, 100, 255)   // yellow when selected
            : IM_COL32(80, 200, 255, 255);   // normal blue

        drawList->AddCircleFilled(pos, radius, color);

        drawList->AddCircle(pos, radius + 2.0f, IM_COL32(255, 255, 255, 80));
    }

    handleCreatureSelection();
    ImGui::End();
}

// ====================== DATA INSPECTOR ======================
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
            auto& dna = selected.brain.dna;     // cleaner
            ImGui::Text("Speed:             %.1f", dna.getSpeed());
            ImGui::Text("Vision Range:      %.1f", dna.getVisionRange());
            ImGui::Text("Size:              %.1f", dna.getSize());
            ImGui::Text("Strength:          %.1f", dna.getStrength());
            ImGui::Text("Is Male:           %s",   dna.getIsMale() ? "Yes" : "No");

            ImGui::Text("Metabolism:        %.2f", dna.getMetabolism());
            ImGui::Text("Energy efficiency: %.2f", dna.getEnergyEfficiency());
            
            ImGui::Text("Aggression:        %.2f", dna.getAggression());
            ImGui::Text("Courage:           %.2f", dna.getCourage());
            ImGui::Text("Curiosity:         %.2f", dna.getCuriosity());
            ImGui::Text("Gregariousness:    %.2f", dna.getGregariousness());
            ImGui::Text("Leader Coefficient:%.2f", dna.getLeaderCoefficient());
            ImGui::Text("Stealth:           %.1f", dna.getStealth());
            ImGui::Text("Creativity:        %.1f", dna.getCreativity());
            ImGui::Text("Intelligence:      %.1f", dna.getIntelligence());

            ImGui::Text("Fertility:         %.1f", dna.getFertility());
            ImGui::Text("Sex Drive:         %.1f", dna.getSexDrive());
            ImGui::Text("Mutation Rate:     %.1f", dna.getMutationRate());
            ImGui::Text("Mutation Rate:     %.3f", dna.getMutationRate());
        }

        ImGui::Separator();

        // === Brain Section ===
        if (ImGui::CollapsingHeader("Brain", ImGuiTreeNodeFlags_DefaultOpen))
        {
            const char* stateName = "Unknown";

            switch (selected.brain.getCurrentState())
            {
                case Brain::State::Wandering:    stateName = "Wandering";    break;
                case Brain::State::SeekingFood:  stateName = "Seeking Food"; break;
                case Brain::State::Fleeing:      stateName = "Fleeing";      break;
                case Brain::State::Hunting:      stateName = "Hunting";      break;
                case Brain::State::Mating:       stateName = "Mating";       break;
                case Brain::State::Resting:      stateName = "Resting";      break;
            }

            ImGui::Text("State:         %s", stateName);
            ImGui::Text("Hunger:        %.2f", selected.brain.getHunger());
            ImGui::Text("Fear:          %.2f", selected.brain.getFear());
            ImGui::Text("Tiredness:     %.2f", selected.brain.getTiredness());
            ImGui::Text("Mating Drive:  %.2f", selected.brain.getMatingDrive());
            ImGui::Text("Anger:         %.2f", selected.brain.getAnger());
        }
    }

    ImGui::End();
}

// ====================== SPAWN ======================
void UIManager::SpawnRandomCreature()
{
    float randomX = static_cast<float>(rand() % simulationScreenWidth);
    float randomY = static_cast<float>(rand() % simulationScreenHeight);

    Creature newCreature(randomX, randomY, simulationScreenWidth, simulationScreenHeight);
    creatures.push_back(newCreature);
}

// ====================== CREATURE SELECTION ======================
void UIManager::handleCreatureSelection()
{
    // Only check for clicks when the Simulation Window is hovered
    if (!ImGui::IsWindowHovered())
        return;
        float x = 0.0f;
        float y = 0.0f;

    // Check for left mouse click
    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {
        ImVec2 mousePos = ImGui::GetMousePos();           // Screen coordinates
        ImVec2 windowPos = ImGui::GetWindowPos();
        ImVec2 contentMin = ImGui::GetWindowContentRegionMin();

        // Convert to world coordinates inside the simulation window
        float worldX = mousePos.x - (windowPos.x + contentMin.x);
        float worldY = mousePos.y - (windowPos.y + contentMin.y);

        // check distance to every creature
        selectedCreatureIndex = -1;     // deselect by default

        for (int i = 0; i < (int)creatures.size(); ++i)
        {
            const Creature& c = creatures[i];

            float dx = worldX - c.getXPos();
            float dy = worldY - c.getYPos();
            float distanceSquared = dx * dx + dy * dy;
            float radius = c.brain.dna.getSize() + 5.0f;        // a bit of extra tolerance

            if (distanceSquared <= radius * radius)
            {
                selectedCreatureIndex = i;
                break;      // stop at the first one hit
            }
        }
    }
}