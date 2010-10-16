#ifndef IMPDUNGEON_LOGIC_NETWORK_EVENTS_TAKEEVENT_H_
#define IMPDUNGEON_LOGIC_NETWORK_EVENTS_TAKEEVENT_H_

#include "logic/network/events/targetedevent.h"

namespace impdungeon {

class TakeEvent : public TargetedEvent {
 public:
  TakeEvent(boost::uuids::uuid &target);
  virtual ~TakeEvent();

  void Accept(EventVisitorInterface &event_visitor);
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_EVENTS_TAKEEVENT_H_
