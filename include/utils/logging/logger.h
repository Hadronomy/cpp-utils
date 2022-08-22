//
// Created by hadronomy on 22/08/22.
//

#pragma once

#ifndef UTILS_LOGGER_H
#define UTILS_LOGGER_H

#include <vector>
#include <memory>

#include "message.h"
#include "transport.h"

namespace utils {

class LoggerMessage;

class Logger {
 public:
  template<class TTransport>
  inline Logger& AddTransport() {
    static_assert(std::is_base_of_v<TTransport, TerminalTransport>);
    transports_.emplace_back(new TTransport);
    return *this;
  }
  void FlagAsDefault() const;
  void Log(const LoggerMessage& msg);

  static Logger GetDefault();

 private:
  std::vector<TerminalTransport*> transports_;
};

static Logger s_default_logger_ = Logger();

}

#endif //UTILS_LOGGER_H
