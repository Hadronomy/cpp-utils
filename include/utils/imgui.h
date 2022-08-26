#pragma once

namespace utils {

template<typename TApp>
class ImApp {
 public:
  ~ImApp() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
  }

  void Update() {
    static_cast<*TApp>
  }
};

}
