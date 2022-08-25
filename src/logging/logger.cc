//
// Created by hadronomy on 22/08/22.
//

#include <iostream>

#include "utils/logging/logger.h"

namespace utils {

void Logger::FlagAsDefault() const {
  s_default_logger_ = *this;
}

Logger Logger::GetDefault() {
  return s_default_logger_;
}

void Logger::Log(const LoggerMessage &msg) {
  for (auto& transport : transports_) {
    transport->Log(msg.str());
  }
}

Logger& Logger::Init() {
  for (auto& transport : transports_) {
    transport->Init();
  }
  return *this;
}

} // utils