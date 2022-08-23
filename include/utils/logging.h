//
// Created by hadronomy on 22/08/22.
//

#pragma once

#ifndef UTILS_LOGGING_H
#define UTILS_LOGGING_H

#include <sstream>
#include <iostream>
#include <vector>
#include <memory>

#endif //UTILS_LOGGING_H

#include "logging/message.h"
#include "logging/logger.h"
#include "logging/transport.h"

namespace utils {

#define LOG(level) utils::LoggerMessage(level).flush()

#define ERROR 0
#define WARN 1
#define INFO 2
#define VERBOSE 3

} // utils
