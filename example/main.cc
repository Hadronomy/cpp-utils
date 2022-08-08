//
// Created by pablo on 08/08/2022.
//

#include <iostream>

#ifdef UTILS_LIB
#include <utils/colors.h>
#include <utils/hourglass.h>
#endif

int main() {
#ifdef UTILS_LIB
  utils::Hourglass::Start();
  std::cout << utils::Colorize(utils::ColorTint::kCyan) << "Hello World! " << utils::Colorize::Reset << std::endl;
  std::cout << utils::Hourglass::Stop();
#endif
  return 0;
}
