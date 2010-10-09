#include "logic/network/events/takeevent.h"

#include "logic/network/events/eventvisitorinterface.h"

namespace impdungeon {

TakeEvent::TakeEvent(boost::uuids::uuid &source, boost::uuids::uuid &target) 
  : Event(source), target_(target) {

}

TakeEvent::~TakeEvent() {

}

void TakeEvent::Accept(EventVisitorInterface &event_visitor) {
  event_visitor.Visit(*this);
}

}  // namespace impdungeon
