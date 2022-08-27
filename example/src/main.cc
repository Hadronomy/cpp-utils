#include <iostream>
#include <filesystem>

#include <utils/info.h>
#include <utils/logger.h>

#define UTILS_PROFILE
#include <utils/instrumentation.h>

#include "gui.h"

int main() {
  UTILS_PROFILE_BEGIN_SESSION("example", "example.profile");
  utils::Logger()
          .AddTransport<utils::TerminalTransport>(LDEBUG)
          .AddTransport<utils::FileTransport>("utils.log", LVERBOSE)
          .Init()
          .FlagAsDefault();
  LOG(LINFO) << "With love from " << UTILS_FUNCSIG << std::endl;
  example::RenderGUI();
  UTILS_PROFILE_END_SESSION();
  return 0;
}
