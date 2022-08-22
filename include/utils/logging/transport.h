//
// Created by hadronomy on 22/08/22.
//

#pragma once

#ifndef UTILS_TRANSPORT_H
#define UTILS_TRANSPORT_H

#include <iostream>
#include <string>

class LoggerTransport {
 public:
  //virtual ~LoggerTransport() = default;

  virtual int GetLevel() = 0;
  virtual void Init() = 0;
  virtual void Log(const std::string& msg) = 0;
};

class TerminalTransport : public LoggerTransport {
 public:
  int GetLevel() override {
    return level_;
  }

  void Init() override {}

  void Log(const std::string& msg) override {
    std::cout << msg;
  }
 private:
  int level_{};
};

#endif //UTILS_TRANSPORT_H
