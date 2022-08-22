//
// Created by pablo on 08/08/2022.
//

#include <iostream>

#include <utils/colors.h>
#include <utils/misc.h>
#include <utils/info.h>
#include <utils/logging.h>
#include <utils/hourglass.h>

class ShoutingPerson {
 public:
  void Shout();
};

void ShoutingPerson::Shout() {
  LOG(INFO) << FILE_NAME << ":" << __LINE__ << " | " << SFUNCTION << std::endl;
}

int main() {
  utils::Logger()
    .AddTransport<TerminalTransport>()
    .FlagAsDefault();
  utils::Hourglass::Start();
  std::cout << utils::Colorize(utils::ColorTint::kCyan) << "Hello World! ";
  std::cout << utils::Colorize::Reset << std::endl;
  std::cout << utils::Hourglass::Stop() << std::endl;
  auto wp = ShoutingPerson();
  wp.Shout();
  utils::Hourglass::Start();
  std::cout << utils::Colorize(utils::ColorTint::kCyan) << "Hello World! " << utils::Colorize::Reset << std::endl;
  std::cout << utils::Hourglass::Stop() << std::endl;
  std::cout << "Press enter to exit";
  utils::WaitForEnter();
  return 0;
}
