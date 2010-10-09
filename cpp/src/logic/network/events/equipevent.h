#ifndef IMPDUNGEON_LOGIC_NETWORK_EVENTS_EQUIPEVENT_H_
#define IMPDUNGEON_LOGIC_NETWORK_EVENTS_EQUIPEVENT_H_

#include "logic/network/events/event.h"

namespace impdungeon {

class EquipEvent : public Event {
 public:
  EquipEvent(boost::uuids::uuid &source, boost::uuids::uuid &target);
  virtual ~EquipEvent();

  void Accept(EventVisitorInterface &event_visitor);

 private:
  boost::uuids::uuid target_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_EVENTS_EQUIPEVENT_H_
