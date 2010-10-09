#include "logic/network/events/attackevent.h"

#include "logic/network/events/eventvisitorinterface.h"

namespace impdungeon {

AttackEvent::AttackEvent(boost::uuids::uuid &source, boost::uuids::uuid &target) 
  : Event(source), target_(target) {

}

AttackEvent::~AttackEvent() {

}

void AttackEvent::Accept(EventVisitorInterface &event_visitor) {
  event_visitor.Visit(*this);
}

}  // namespace impdungeon
