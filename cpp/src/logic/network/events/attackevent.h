#ifndef IMPDUNGEON_LOGIC_NETWORK_EVENTS_ATTACKEVENT_H_
#define IMPDUNGEON_LOGIC_NETWORK_EVENTS_ATTACKEVENT_H_

#include "logic/network/events/targetedplayerevent.h"

namespace impdungeon {

class AttackEvent : public TargetedPlayerEvent {
 public:
  AttackEvent(boost::uuids::uuid &source, boost::uuids::uuid &target);
  virtual ~AttackEvent();

  void Accept(EventVisitorInterface &event_visitor);
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_EVENTS_ATTACKEVENT_H_
