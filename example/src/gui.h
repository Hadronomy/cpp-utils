#pragma once

#include <imgui/imgui.h>

namespace example {

void Update();
int RenderGUI();
void ShowDocking();
void ShowRightPanel();
void SetupTheme(const ImGuiIO& io);

}
