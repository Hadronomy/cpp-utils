//
// Created by pablo on 08/08/2022.
//

#include <iostream>

#include <utils/colors.h>
#include <utils/misc.h>
#include <utils/info.h>
#include <utils/logging.h>
#include <utils/hourglass.h>

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

void ShowDocking();

void ShowRightPanel();

void SetupTheme(const ImGuiIO&);

static void glfw_error_callback(int error, const char* description)
{
  LOG(ERROR) << "glfw Error "<< error << ": " << description;
}

int main() {
  utils::Logger()
    .AddTransport<TerminalTransport>()
    .AddTransport<FileTransport>("/home/hadronomy/utils-log")
    .Init()
    .FlagAsDefault();
  utils::Hourglass::Start();
  // Window setup
  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit())
    return 1;
#if defined(IMGUI_IMPL_OPENGL_ES2)
  // GL ES 2.0 + GLSL 100
  const char* glsl_version = "#version 100";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
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
  ImVec4 background_color = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
  LOG(INFO) << "Initialized\t" << utils::Hourglass::Stop().Elapsed() << "ms" << std::endl;
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ShowDocking();
    ShowRightPanel();
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
  window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
  ImGui::Begin("Dockspace", nullptr, window_flags);
  ImGui::BeginMenuBar();
  ImGui::Text("Example");
  ImGui::EndMenuBar();
  auto dockspace_id = ImGui::GetID("Dockspace");
  ImGui::DockSpace(dockspace_id);
  ImGui::ShowDemoWindow();

  ImGui::End();

  ImGui::PopStyleVar(3);
}

void ShowRightPanel() {
  ImGui::Begin("Tools");
  ImGui::End();
}

void SetupTheme(const ImGuiIO& io) {
  io.Fonts->AddFontFromFileTTF("data/Fonts/Ruda-VariableFont_wght.ttf", 16.0f);
  ImVec4* colors = ImGui::GetStyle().Colors;
  colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
  colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
  colors[ImGuiCol_WindowBg]               = ImVec4(0.14f, 0.14f, 0.15f, 1.00f);
  colors[ImGuiCol_ChildBg]                = ImVec4(0.14f, 0.14f, 0.15f, 1.00f);
  colors[ImGuiCol_PopupBg]                = ImVec4(0.14f, 0.14f, 0.15f, 1.00f);
  colors[ImGuiCol_Border]                 = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
  colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_FrameBg]                = ImVec4(0.47f, 0.48f, 0.49f, 0.54f);
  colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.55f, 0.55f, 0.56f, 0.54f);
  colors[ImGuiCol_FrameBgActive]          = ImVec4(0.47f, 0.48f, 0.49f, 0.54f);
  colors[ImGuiCol_TitleBg]                = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
  colors[ImGuiCol_TitleBgActive]          = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
  colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
  colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
  colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
  colors[ImGuiCol_CheckMark]              = ImVec4(1.00f, 0.76f, 0.22f, 1.00f);
  colors[ImGuiCol_SliderGrab]             = ImVec4(0.55f, 0.57f, 0.59f, 1.00f);
  colors[ImGuiCol_SliderGrabActive]       = ImVec4(1.00f, 0.76f, 0.22f, 1.00f);
  colors[ImGuiCol_Button]                 = ImVec4(0.47f, 0.48f, 0.49f, 0.54f);
  colors[ImGuiCol_ButtonHovered]          = ImVec4(0.55f, 0.55f, 0.56f, 0.54f);
  colors[ImGuiCol_ButtonActive]           = ImVec4(0.66f, 0.66f, 0.66f, 1.00f);
  colors[ImGuiCol_Header]                 = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
  colors[ImGuiCol_HeaderHovered]          = ImVec4(0.31f, 0.31f, 0.30f, 1.00f);
  colors[ImGuiCol_HeaderActive]           = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
  colors[ImGuiCol_Separator]              = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
  colors[ImGuiCol_SeparatorHovered]       = ImVec4(1.00f, 0.76f, 0.22f, 1.00f);
  colors[ImGuiCol_SeparatorActive]        = ImVec4(1.00f, 0.90f, 0.71f, 1.00f);
  colors[ImGuiCol_ResizeGrip]             = ImVec4(0.55f, 0.57f, 0.59f, 1.00f);
  colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.59f, 0.60f, 0.62f, 1.00f);
  colors[ImGuiCol_ResizeGripActive]       = ImVec4(1.00f, 0.76f, 0.22f, 1.00f);
  colors[ImGuiCol_Tab]                    = ImVec4(0.27f, 0.27f, 0.26f, 0.86f);
  colors[ImGuiCol_TabHovered]             = ImVec4(1.00f, 0.76f, 0.22f, 0.41f);
  colors[ImGuiCol_TabActive]              = ImVec4(1.00f, 0.76f, 0.22f, 0.52f);
  colors[ImGuiCol_TabUnfocused]           = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
  colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(1.00f, 0.76f, 0.22f, 0.52f);
  colors[ImGuiCol_DockingPreview]         = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
  colors[ImGuiCol_DockingEmptyBg]         = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
  colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
  colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
  colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
  colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
  colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
  colors[ImGuiCol_TableBorderLight]       = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
  colors[ImGuiCol_TableRowBg]             = ImVec4(0.34f, 0.34f, 0.34f, 0.00f);
  colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
  colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.98f, 0.74f, 0.26f, 0.35f);
  colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 0.71f, 0.00f, 0.90f);
  colors[ImGuiCol_NavHighlight]           = ImVec4(0.59f, 0.60f, 0.62f, 1.00f);
  colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
  colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
  colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}
