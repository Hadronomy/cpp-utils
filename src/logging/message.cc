#include "utils/logger.h"

void utils::LoggerMessage::Log() const {
  Logger::GetDefault().Log(*this);
}