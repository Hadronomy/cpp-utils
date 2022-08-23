//
// Created by hadronomy on 22/08/22.
//

#pragma once

#ifndef UTILS_TRANSPORT_H
#define UTILS_TRANSPORT_H

#include <iostream>
#include <string>
#include <fstream>

class BaseTransport {
 public:
  virtual ~BaseTransport() = default;

  virtual int GetLevel() = 0;
  virtual void Init() = 0;
  virtual void Log(const std::string& msg) = 0;
};

class TerminalTransport : public BaseTransport {
 public:
  ~TerminalTransport() override {}
  int GetLevel() override { return level_; }
  void Init() override {}
  void Log(const std::string& msg) override {
    std::cout << msg;
  }
 private:
  int level_ = 0;
};

class FileTransport : public BaseTransport {
 public:
  FileTransport(const std::string& path) : path_(path), BaseTransport() {}
  ~FileTransport() override { file_.close(); }

  int GetLevel() override { return level_; };

  void Init() override {
    file_ = std::ofstream(path_);
    if (!file_.is_open())
      std::cout << "Could not open file at path " << path_ << std::endl;
    return;
  }

  void Log(const std::string& msg) override {
    file_.flush() << msg;
  }
 private:
  int level_ = 0;
  std::string path_;
  std::ofstream file_;
};

#endif //UTILS_TRANSPORT_H
