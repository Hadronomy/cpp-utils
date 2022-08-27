#pragma once

#include <imgui.h>

class GLFWwindow;
class ImGuiIO;

namespace example {

void Update(GLFWwindow* window, ImGuiIO& io);
int RenderGUI();
void ShowDocking();
void ShowRightPanel();
void SetupTheme(const ImGuiIO& io);

}
