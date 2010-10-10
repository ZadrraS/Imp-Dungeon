#ifndef IMPDUNGEON_LOGIC_NETWORK_EVENTS_EQUIPEVENT_H_
#define IMPDUNGEON_LOGIC_NETWORK_EVENTS_EQUIPEVENT_H_

#include "logic/network/events/targetedplayerevent.h"

namespace impdungeon {

class EquipEvent : public TargetedPlayerEvent {
 public:
  EquipEvent(boost::uuids::uuid &source, boost::uuids::uuid &target);
  virtual ~EquipEvent();

  void Accept(EventVisitorInterface &event_visitor);
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_EVENTS_EQUIPEVENT_H_
