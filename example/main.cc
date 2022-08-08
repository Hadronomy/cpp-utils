//
// Created by pablo on 08/08/2022.
//

#include <iostream>

#include <utils/colors.h>
#include <utils/hourglass.h>

int main() {
  utils::Hourglass::Start();
  std::cout << utils::Colorize(utils::ColorTint::kCyan) << "Hello World! " << utils::Colorize::Reset << std::endl;
  std::cout << utils::Hourglass::Stop();
  return 0;
}
