//
// Created by hadronomy on 22/08/22.
//

#pragma once

#ifndef UTILS_MESSAGE_H
#define UTILS_MESSAGE_H

#include <sstream>

#include "logger.h"

namespace utils {

class LoggerMessage : public std::ostringstream {
 public:
  explicit LoggerMessage(const int level) : level_(level) {}

  ~LoggerMessage() override {
    Log();
  }

 private:
  void Log() const;

  int level_ = 0;
};

}

#endif //UTILS_MESSAGE_H
