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

void UIManager::renderSimulationScreen()
{
    ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(simulationScreenWidth, simulationScreenHeight), ImGuiCond_FirstUseEver);

    ImGui::Begin("Simulation Window");

    // Get the top-left position of the content region
    ImVec2 origin = ImGui::GetCursorScreenPos();   // This is the key!

    Creature testCreature(200.0f, 200.0f);

    ImDrawList* drawList = ImGui::GetWindowDrawList();

    ImVec2 pos = ImVec2(
        origin.x + testCreature.x,
        origin.y + testCreature.y
    );

    drawList->AddCircleFilled(pos, 15.0f, IM_COL32(255, 100, 180, 255));

    // Optional: Show some info
    ImGui::Text("Creature at: (%.0f, %.0f)", testCreature.x, testCreature.y);

    ImGui::End();
}