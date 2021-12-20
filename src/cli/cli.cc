#include <algorithm>
#include <iostream>
#include <iomanip>
#include <exception>

#include "cli.h"
#include "colors.h"
#include "misc/exceptions.h"

namespace utils {

void Cli::Parse(const int arg_count, char* pased_args[]) {
  SetBinary(pased_args[0]);
  ParseCommand(arg_count, pased_args);
  return;
}

}