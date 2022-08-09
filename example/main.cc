//
// Created by pablo on 08/08/2022.
//

#include <iostream>

#ifdef UTILS_LIB
#include <utils/colors.h>
#include <utils/hourglass.h>
#include <utils/events.h>
#endif

struct EventMessage {
  std::string author;
  std::string msg;
  bool is_awesome;
};

int main() {
#ifdef UTILS_LIB
  utils::Hourglass::Start();
  std::cout << utils::Colorize(utils::ColorTint::kCyan) << "Hello World! ";
  std::cout << utils::Colorize::Reset << std::endl;
  auto event_manager = StrEventManager<std::string>();
  event_manager.On("message", [](std::string msg) {
    std::cout << "Shhh te ha llegado un mensaje" << std::endl;
  });
  event_manager.On("message", [](std::string msg) {
    std::cout << msg << std::endl;
  });
  event_manager.Trigger("message", "HEHE");
  event_manager.Trigger("HEHE", "");
  std::cout << utils::Hourglass::Stop();
#endif
  return 0;
}
