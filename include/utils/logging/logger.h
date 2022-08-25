//
// Created by hadronomy on 22/08/22.
//

#pragma once

#ifndef UTILS_LOGGER_H
#define UTILS_LOGGER_H

#include <vector>
#include <memory>
#include <cstdarg>

#include "message.h"
#include "transport.h"

namespace utils {

class LoggerMessage;

class Logger {
 public:
  template<class TTransport, typename... Args>
  inline Logger& AddTransport(Args... args) {
    static_assert(std::is_base_of_v<BaseTransport, TTransport>);
    transports_.emplace_back(std::make_shared<TTransport>(args...));
    return *this;
  }
  Logger& Init();
  void FlagAsDefault() const;
  void Log(const LoggerMessage& msg);

  static Logger GetDefault();

 private:
  std::vector<std::shared_ptr<BaseTransport>> transports_;
};

static Logger s_default_logger_ = Logger();

}

#endif //UTILS_LOGGER_H
