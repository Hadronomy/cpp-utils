//
// Created by hadronomy on 22/08/22.
//

#pragma once

#include <string>

#include "logger.h"

namespace utils {

#ifdef __FUNCDNAME__
  #define UTILS_FUNCSIG __FUNCSIG__
#elif __PRETTY_FUNCTION__
  #define UTILS_FUNCSIG __PRETTY_FUNCTION__
#endif
#ifndef UTILS_FUNCSIG
  #define UTILS_FUNCSIG __func__
#endif

#define FILE_NAME (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 : __FILE__)
#define SFUNCTION (__builtin_strrchr(UTILS_FUNCSIGN, ' ') ? __builtin_strrchr(UTILS_FUNCSIGN, ' ') + 1 : UTILS_FUNCSIGN)


} // utils
