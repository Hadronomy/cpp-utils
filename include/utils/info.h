//
// Created by hadronomy on 22/08/22.
//

#pragma once

#ifndef UTILS_INFO_H
#define UTILS_INFO_H

#include <string>

namespace utils {

#define FILE_NAME (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 : __FILE__)
#define SFUNCTION (__builtin_strrchr(__PRETTY_FUNCTION__, ' ') ? __builtin_strrchr(__PRETTY_FUNCTION__, ' ') + 1 : __PRETTY_FUNCTION__)

} // utils

#endif //UTILS_INFO_H
