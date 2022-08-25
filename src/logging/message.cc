//
// Created by hadronomy on 22/08/22.
//

#include "utils/logging/message.h"
#include "utils/logging/logger.h"

void utils::LoggerMessage::Log() const {
  Logger::GetDefault().Log(*this);
}