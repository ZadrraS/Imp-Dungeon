#include "logic/network/events/dropevent.h"

#include "logic/network/events/eventvisitorinterface.h"

namespace impdungeon {

DropEvent::DropEvent(boost::uuids::uuid &target) 
  : TargetedEvent(target) {

}

DropEvent::~DropEvent() {

}

void DropEvent::Accept(EventVisitorInterface &event_visitor) {
  event_visitor.Visit(*this);
}

}  // namespace impdungeon
