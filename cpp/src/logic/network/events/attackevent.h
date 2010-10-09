#ifndef IMPDUNGEON_LOGIC_NETWORK_EVENTS_ATTACKEVENT_H_
#define IMPDUNGEON_LOGIC_NETWORK_EVENTS_ATTACKEVENT_H_

#include "logic/network/events/event.h"

namespace impdungeon {

class AttackEvent : public Event {
 public:
  AttackEvent(boost::uuids::uuid &source, boost::uuids::uuid &target);
  virtual ~AttackEvent();

  void Accept(EventVisitorInterface &event_visitor);

 private:
  boost::uuids::uuid target_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_EVENTS_ATTACKEVENT_H_
