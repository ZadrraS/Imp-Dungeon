#include "logic/network/events/equipevent.h"

#include "logic/network/events/eventvisitorinterface.h"

namespace impdungeon {

EquipEvent::EquipEvent(boost::uuids::uuid &source, boost::uuids::uuid &target) 
  : TargetedPlayerEvent(source, target) {

}

EquipEvent::~EquipEvent() {

}

void EquipEvent::Accept(EventVisitorInterface &event_visitor) {
  event_visitor.Visit(*this);
}

}  // namespace impdungeon
