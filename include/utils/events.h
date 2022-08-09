//
// Created by hadronomy on 8/08/22.
//

#ifndef UTILS_EVENTS_H
#define UTILS_EVENTS_H

#include <string>
#include <functional>
#include <map>
#include <iostream>
#include <vector>

template<class TCallback>
class StrEventManager {
 public:
  typedef std::function<void(const TCallback)> EventAction;

  StrEventManager() : action_map_() {}

  void On(const std::string& name, const EventAction& action);
  void Trigger(const std::string &name, const TCallback &callback);

 private:
  std::map<std::string, std::vector<EventAction>> action_map_;
};

template<class TCallback>
void StrEventManager<TCallback>::On(const std::string &name, const EventAction& action) {
  if (action_map_.count(name) == 0)
    action_map_[name] = std::vector<EventAction>();
  action_map_.at(name).push_back(action);
}

template<class TCallback>
void StrEventManager<TCallback>::Trigger(
        const std::string &name,
        const TCallback &callback) {
  if (action_map_.count(name) == 0) {
    std::cerr << "Invalid event name" << std::endl;
    return;
  }
  for (auto& action : action_map_.at(name)) {
    action(callback);
  }
  typename std::map<std::string, std::vector<EventAction>>::iterator it = action_map_.find(name);
  action_map_.erase(it);
}

#endif //UTILS_EVENTS_H
