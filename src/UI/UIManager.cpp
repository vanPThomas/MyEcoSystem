#include "imgui.h"
#include "UIManager.h"

void ShowHelloWindow()
{
    ImGui::Begin("Hello From another file.");
    ImGui::Text("This window is drawn from another file");
    ImGui::End();
}