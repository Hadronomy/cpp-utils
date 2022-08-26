//
// Created by pablo on 08/08/2022.
//

#include <iostream>
#include <filesystem>

#include <utils/info.h>
#include <utils/logger.h>

#include "gui.h"

int main() {
  utils::Logger()
          .AddTransport<utils::TerminalTransport>(LDEBUG)
          .AddTransport<utils::FileTransport>("utils.log", LVERBOSE)
          .Init()
          .FlagAsDefault();
  LOG(LINFO) << "With love from " << UTILS_FUNCSIG << std::endl;
  return example::RenderGUI();
}
