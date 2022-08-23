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
    .AddTransport<FileTransport>("/home/hadronomy/utils-log")
    .Init()
    .FlagAsDefault();
  utils::Hourglass::Start();
  LOG(INFO) << utils::Colorize(utils::FontStyle::kBold);
  LOG(INFO) << utils::Colorize(utils::ColorTint::kCyan) << "Hello World! ";
  LOG(INFO) << utils::Colorize::Reset << std::endl;
  LOG(INFO) << utils::Hourglass::Stop() << std::endl;
  utils::Hourglass::Start();
  auto wp = ShoutingPerson();
  wp.Shout();
  LOG(INFO) << utils::Hourglass::Stop();
  return 0;
}
