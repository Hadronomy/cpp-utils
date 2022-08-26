#include "utils/logger.h"

namespace utils {

void TerminalTransport::Log(const LoggerMessage& msg) {
  if (msg.GetLevel() > level_ || level_ == LOFF) return;
  if (msg.GetLevel() & LOG_LEVEL_ERROR) {
    std::cerr << msg.str();
    return;
  }
  std::cout << msg.str();
}

void FileTransport::Log(const LoggerMessage& msg) {
  file_.flush() << msg.str();
}

void FileTransport::Init() {
  file_ = std::ofstream(path_);
  if (!file_.is_open())
    std::cout << "Could not open file at path " << path_ << std::endl;
}

}

