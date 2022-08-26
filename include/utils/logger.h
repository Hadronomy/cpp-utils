#pragma once

#include <sstream>
#include <iostream>
#include <vector>
#include <memory>
#include <fstream>

namespace utils {

#define LOG(level) utils::LoggerMessage(level).flush()

/**
 * Standard log levels
 */
enum LogLevel : uint_fast8_t {
  LOG_LEVEL_OFF     = 0,
  LOG_LEVEL_FATAL   = 1 << 1,
  LOG_LEVEL_ERROR   = 1 << 2,
  LOG_LEVEL_WARN    = 1 << 3,
  LOG_LEVEL_INFO    = 1 << 4,
  LOG_LEVEL_DEBUG   = 1 << 5,
  LOG_LEVEL_TRACE   = 1 << 6,
  LOG_LEVEL_VERBOSE = 1 << 7,
};

#define LOFF     utils::LOG_LEVEL_OFF
#define LFATAL   utils::LOG_LEVEL_FATAL
#define LERROR   utils::LOG_LEVEL_ERROR
#define LWARN    utils::LOG_LEVEL_WARN
#define LINFO    utils::LOG_LEVEL_INFO
#define LDEBUG   utils::LOG_LEVEL_DEBUG
#define LTRACE   utils::LOG_LEVEL_TRACE
#define LVERBOSE utils::LOG_LEVEL_VERBOSE

class BaseTransport;
class LoggerMessage;

/**
 * Defines basic logging functionality
 */
class Logger {
 public:
  template<class TTransport, typename... Args>
  Logger& AddTransport(Args... args);
  Logger& Init();
  void FlagAsDefault() const;
  void Log(const LoggerMessage& msg);

  static Logger GetDefault();

 private:
  std::vector<std::shared_ptr<BaseTransport>> transports_;
};

static Logger s_default_logger_ = Logger();

template<class TTransport, typename... Args>
inline Logger& Logger::AddTransport(Args... args) {
  static_assert(std::is_base_of_v<BaseTransport, TTransport>);
  transports_.emplace_back(std::make_shared<TTransport>(args...));
  return *this;
}

/**
 * Carries the message information to the logger
 */
class LoggerMessage : public std::ostringstream {
 public:
  explicit LoggerMessage(const LogLevel& level) : level_(level) {}
  ~LoggerMessage() override {
    Log();
  }

  LogLevel GetLevel() const { return level_; }

 private:
  void Log() const;

  LogLevel level_;
};

/**
 * @brief
 * Base class for implementation of logger transports.
 * Logger transports are responsible for "transporting"
 * the %LoggerMessage%s to a destination. For example,
 * the standard output.
 */
class BaseTransport {
 public:
  virtual ~BaseTransport() = default;

  virtual LogLevel GetLevel() = 0;
  virtual void Init() = 0;
  virtual void Log(const LoggerMessage& msg) = 0;
};

/**
 * @brief
 * Basic implementation of a terminal transports.
 * Logs the incoming messages to the
 * standard outputs.
 */
class TerminalTransport : public BaseTransport {
 public:
  explicit TerminalTransport(const LogLevel& level) : level_(level) {}
  ~TerminalTransport() override {}

  LogLevel GetLevel() override { return level_; }
  void Init() override {}
  void Log(const LoggerMessage& msg) override;

 private:
  LogLevel level_;
};

/**
 * @brief
 * Basic implementation of a file transport.
 * Logs the incoming messages to an specified file.
 */
class FileTransport : public BaseTransport {
 public:
  explicit FileTransport(std::string path, LogLevel level) :
          path_(std::move(path)), level_(level), BaseTransport() {}
  ~FileTransport() override { file_.close(); }

  LogLevel GetLevel() override { return level_; }
  void Init() override;
  void Log(const LoggerMessage& msg) override;

 private:
  LogLevel level_;
  std::string path_;
  std::ofstream file_;
};

} // utils
