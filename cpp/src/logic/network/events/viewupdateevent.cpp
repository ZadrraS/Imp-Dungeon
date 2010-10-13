#include "logic/network/events/viewupdateevent.h"

#include "logic/network/events/eventvisitorinterface.h"

namespace impdungeon {

ViewUpdateEvent::ViewUpdateEvent(boost::uuids::uuid &source) 
  : PlayerEvent(source) {

}

ViewUpdateEvent::~ViewUpdateEvent() {

}

void ViewUpdateEvent::Accept(EventVisitorInterface &event_visitor) {
  event_visitor.Visit(*this);
}

}  // namespace impdungeon
