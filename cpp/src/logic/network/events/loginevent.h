#ifndef IMPDUNGEON_LOGIC_NETWORK_EVENTS_LOGINEVENT_H_
#define IMPDUNGEON_LOGIC_NETWORK_EVENTS_LOGINEVENT_H_

#include "logic/network/events/event.h"

#include <string>

namespace impdungeon {

class LoginEvent : public Event {
 public:
  LoginEvent(boost::uuids::uuid &source, 
             const std::string &user_name, 
             const std::string &password);
  virtual ~LoginEvent();

  void Accept(EventVisitorInterface &event_visitor);

 private:
  std::string user_name_;
  std::string password_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_EVENTS_LOGINEVENT_H_
