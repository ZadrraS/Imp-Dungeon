#include "logic/network/events/loginevent.h"

#include "logic/network/events/eventvisitorinterface.h"

namespace impdungeon {

LoginEvent::LoginEvent(boost::uuids::uuid &source, 
                       const std::string &user_name, 
                       const std::string &password) 
  : Event(source), user_name_(user_name), password_(password) {

}

LoginEvent::~LoginEvent() {

}

void LoginEvent::Accept(EventVisitorInterface &event_visitor) {
  event_visitor.Visit(*this);
}

}  // namespace impdungeon
