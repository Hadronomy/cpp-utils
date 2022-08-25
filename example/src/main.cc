//
// Created by pablo on 08/08/2022.
//

#include <iostream>

#include "utils/colors.h"
#include "utils/misc.h"
#include "utils/info.h"
#include "utils/logging.h"
#include "utils/hourglass.h"

#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_stdlib.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

void ShowDocking();

void ShowRightPanel();

void SetupTheme(const ImGuiIO&);

int RenderGUI();

static void glfw_error_callback(int error, const char* description)
{
  LOG(ERROR) << "glfw Error "<< error << ": " << description;
}

int main() {
  utils::Logger()
    .AddTransport<TerminalTransport>()
    .AddTransport<FileTransport>("utils-log")
    .Init()
    .FlagAsDefault();
  LOG(INFO) << "With love from " << UTILS_FUNCSIG << std::endl;
  return RenderGUI();
}

int RenderGUI() {
  utils::Hourglass::Start();
  // Window setup
  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit())
    return 1;
#ifdef IMGUI_IMPL_OPENGL_ES2
  // GL ES 2.0 + GLSL 100
  const char* glsl_version = "#version 100";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif __APPLE__
  // GL 3.2 + GLSL 150
  const char* glsl_version = "#version 150";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
  // GL 3.0 + GLSL 130
  const char* glsl_version = "#version 130";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
  //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif
  GLFWwindow* window = glfwCreateWindow(1080, 720, "Example", nullptr, nullptr);
  if (window == nullptr)
    return 1;
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);
  // Setup DearImGui
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);
  // Set window style
  ImGuiStyle& style = ImGui::GetStyle();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }
  SetupTheme(io);
  LOG(INFO) << "Initialized\t" << utils::Hourglass::Stop().Elapsed() << "ms" << std::endl;
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ShowDocking();
    ShowRightPanel();

    if (ImGui::Begin("TTY")) {
      static char tty_path[128] = "/dev/pts/0";
      ImGui::Text("TTY");
      ImGui::SameLine();
      ImGui::InputText("##tty_path", tty_path, sizeof(tty_path));

      static char msg[128] = "";
      ImGui::Text("Message");
      ImGui::SameLine();
      ImGui::InputText("##tty_msg", msg, sizeof(msg));

      static std::fstream tty;
      if (ImGui::Button("Connect")) {
        tty.close();
        tty.open(tty_path);
      }
      ImGui::SameLine();
      if (ImGui::Button("Send") && tty.is_open()) {
        tty << msg << std::endl;
        tty.flush();
      }

      ImGui::End();
    }
    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    // Update and Render additional Platform Windows
    // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
    //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
      GLFWwindow* backup_current_context = glfwGetCurrentContext();
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
      glfwMakeContextCurrent(backup_current_context);
    }

    glfwSwapBuffers(window);
  }
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

void ShowDocking() {
  ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
  const ImGuiViewport* viewport = ImGui::GetMainViewport();
  // Setup fullscreen style
  ImGui::SetNextWindowPos(viewport->WorkPos);
  ImGui::SetNextWindowSize(viewport->WorkSize);
  ImGui::SetNextWindowViewport(viewport->ID);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
  window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;
  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_AlwaysAutoResize;

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
  if (ImGui::Begin("Dockspace", nullptr, window_flags)) {
    ImGui::PopStyleVar();
    ImGui::BeginMenuBar();
    ImGui::Text("Example");
    ImGui::EndMenuBar();
    auto dockspace_id = ImGui::GetID("Dockspace");
    ImGui::DockSpace(dockspace_id);
    ImGui::ShowDemoWindow();
    ImGui::PopStyleVar(2);
    ImGui::End();
  }
}

void ShowRightPanel() {
  if (ImGui::Begin("Tools")) {
    ImGui::End();
  }
}

void SetupTheme(const ImGuiIO& io) {
  io.Fonts->AddFontFromFileTTF("data/Fonts/Ruda-VariableFont_wght.ttf", 16.0f);

  ImGuiWindowClass windowClass;
  windowClass.ViewportFlagsOverrideSet |= ImGuiDockNodeFlags_NoWindowMenuButton;

  ImGuiStyle& style = ImGui::GetStyle();
  // style.WindowMenuButtonPosition          = ImGuiDir_None;
  style.WindowBorderSize                  = 0.50f;
  style.TabRounding                       = 2.30f;
  style.FrameRounding                     = 2.30f;
  style.GrabRounding                      = 1.00f;
  style.WindowPadding                     = ImVec2(10.0f, 8.00f);
  style.WindowTitleAlign                  = ImVec2(0.50f, 0.50f);

  constexpr auto ColorFromBytes = [](uint8_t r, uint8_t g, uint8_t b)
  {
    return ImVec4((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, 1.0f);
  };

  ImVec4* colors = style.Colors;
  const ImVec4 darkBgColor       = ColorFromBytes(25, 25, 25);
  const ImVec4 bgColor           = ColorFromBytes(37, 37, 38);
  const ImVec4 lightBgColor      = ColorFromBytes(82, 82, 85);
  const ImVec4 veryLightBgColor  = ColorFromBytes(120, 120, 125);

  const ImVec4 panelColor        = darkBgColor;
  const ImVec4 panelHoverColor   = ColorFromBytes(50, 50, 50);
  const ImVec4 panelActiveColor  = ColorFromBytes(20, 20, 21);

  const ImVec4 textColor         = ColorFromBytes(255, 255, 255);
  const ImVec4 textDisabledColor = ColorFromBytes(151, 151, 151);
  const ImVec4 borderColor       = ColorFromBytes(78, 78, 78);

  const ImVec4 accentColor       = ColorFromBytes(100, 100, 200);

  colors[ImGuiCol_Text]                 = textColor;
  colors[ImGuiCol_TextDisabled]         = textDisabledColor;
  colors[ImGuiCol_TextSelectedBg]       = accentColor;
  colors[ImGuiCol_WindowBg]             = bgColor;
  colors[ImGuiCol_ChildBg]              = bgColor;
  colors[ImGuiCol_PopupBg]              = bgColor;
  colors[ImGuiCol_Border]               = borderColor;
  colors[ImGuiCol_BorderShadow]         = borderColor;
  colors[ImGuiCol_FrameBg]              = panelColor;
  colors[ImGuiCol_FrameBgHovered]       = panelHoverColor;
  colors[ImGuiCol_FrameBgActive]        = panelActiveColor;
  colors[ImGuiCol_TitleBg]              = darkBgColor;
  colors[ImGuiCol_TitleBgActive]        = darkBgColor;
  colors[ImGuiCol_TitleBgCollapsed]     = darkBgColor;
  colors[ImGuiCol_MenuBarBg]            = darkBgColor;
  colors[ImGuiCol_ScrollbarBg]          = darkBgColor;
  colors[ImGuiCol_ScrollbarGrab]        = lightBgColor;
  colors[ImGuiCol_ScrollbarGrabHovered] = veryLightBgColor;
  colors[ImGuiCol_ScrollbarGrabActive]  = veryLightBgColor;
  colors[ImGuiCol_CheckMark]            = accentColor;
  colors[ImGuiCol_SliderGrab]           = lightBgColor;
  colors[ImGuiCol_SliderGrabActive]     = veryLightBgColor;
  colors[ImGuiCol_Button]               = panelColor;
  colors[ImGuiCol_ButtonHovered]        = panelHoverColor;
  colors[ImGuiCol_ButtonActive]         = panelActiveColor;
  colors[ImGuiCol_Header]               = panelColor;
  colors[ImGuiCol_HeaderHovered]        = panelHoverColor;
  colors[ImGuiCol_HeaderActive]         = panelActiveColor;
  colors[ImGuiCol_Separator]            = borderColor;
  colors[ImGuiCol_SeparatorHovered]     = borderColor;
  colors[ImGuiCol_SeparatorActive]      = borderColor;
  colors[ImGuiCol_ResizeGrip]           = bgColor;
  colors[ImGuiCol_ResizeGripHovered]    = panelColor;
  colors[ImGuiCol_ResizeGripActive]     = lightBgColor;
  colors[ImGuiCol_PlotLines]            = lightBgColor;
  colors[ImGuiCol_PlotLinesHovered]     = veryLightBgColor;
  colors[ImGuiCol_PlotHistogram]        = lightBgColor;
  colors[ImGuiCol_PlotHistogramHovered] = veryLightBgColor;
  colors[ImGuiCol_ModalWindowDimBg]     = bgColor;
  colors[ImGuiCol_DragDropTarget]       = accentColor;
  colors[ImGuiCol_NavHighlight]         = accentColor;
  colors[ImGuiCol_DockingPreview]       = accentColor;
  colors[ImGuiCol_Tab]                  = bgColor;
  colors[ImGuiCol_TabActive]            = lightBgColor;
  colors[ImGuiCol_TabUnfocused]         = bgColor;
  colors[ImGuiCol_TabUnfocusedActive]   = bgColor;
  colors[ImGuiCol_TabHovered]           = veryLightBgColor;
}
