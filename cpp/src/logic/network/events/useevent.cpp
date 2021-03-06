#include "logic/network/events/useevent.h"

#include "logic/network/events/eventvisitorinterface.h"

namespace impdungeon {

UseEvent::UseEvent(boost::uuids::uuid &target) 
  : TargetedEvent(target) {

}

UseEvent::~UseEvent() {

}

void UseEvent::Accept(EventVisitorInterface &event_visitor) {
  event_visitor.Visit(*this);
}

}  // namespace impdungeon
