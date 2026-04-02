#include "../includes/imgui.h"
#include "../includes/imgui_impl_glfw.h"
#include "../includes/imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>
#include <iostream>

#include "./UI/UIManager.h"

// Optional includes (for your project later)
// #include <vector>
// #include <string>
// #include <cmath>
// #include <random>
// #include <sys/statvfs.h>
// #include <SDL2/SDL.h>
// #include <algorithm>

int main(int argc, char **argv)
{

    // Initialize GLFW
    if (!glfwInit())
        return 1;

    // Set OpenGL version (optional, depending on your driver support)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment for macOS

    // Create window
    GLFWwindow *window = glfwCreateWindow(1280, 720, "EcoSystem", NULL, NULL);
    if (!window)
    {
        std::cout << "error" << std::endl;
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 150");

    // Load custom font
    ImFont *customFont = io.Fonts->AddFontFromFileTTF("fonts/Px437_IBM_VGA_8x14.ttf", 18.0f);
    if (!customFont)
    {
        std::cerr << "Failed to load font!" << std::endl;
        return 1;
    }

    while (!glfwWindowShouldClose(window))
    {
        // Poll and handle events
        glfwPollEvents();

        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Push font and style if needed
        ImGui::PushFont(customFont);
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 0, 1)); // Example
        {
            // Your ImGui drawing here
            ImGui::Begin("Hello World");
            ImGui::Text("Behavioral AI system starting...");
            ImGui::End();
        }
        {
            // Your ImGui drawing here
            ImGui::Begin("Hello World");
            ImGui::Text("Behavioral AI system starting...");
            ImGui::End();
        }
        ShowHelloWindow();

        // Pop before render
        ImGui::PopFont();
        ImGui::PopStyleColor();

        // Render frame
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}