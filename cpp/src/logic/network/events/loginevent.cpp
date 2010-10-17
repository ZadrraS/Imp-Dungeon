#include "logic/network/events/loginevent.h"

#include "logic/network/events/eventvisitorinterface.h"
#include <iostream>
namespace impdungeon {

LoginEvent::LoginEvent(const std::string &user_name, 
                       const std::string &password) 
  : user_name_(user_name), password_(password) {

}

LoginEvent::~LoginEvent() {

}

void LoginEvent::Accept(EventVisitorInterface &event_visitor) {
  event_visitor.Visit(*this);
}

std::string LoginEvent::user_name() {
  return user_name_;
}
std::string LoginEvent::password() {
  return password_;
}


}  // namespace impdungeon
