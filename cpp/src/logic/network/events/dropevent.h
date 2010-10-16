#ifndef IMPDUNGEON_LOGIC_NETWORK_EVENTS_DROPEVENT_H_
#define IMPDUNGEON_LOGIC_NETWORK_EVENTS_DROPEVENT_H_

#include "logic/network/events/targetedevent.h"

namespace impdungeon {

class DropEvent : public TargetedEvent {
 public:
  DropEvent(boost::uuids::uuid &target);
  virtual ~DropEvent();

  void Accept(EventVisitorInterface &event_visitor);
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_EVENTS_DROPEVENT_H_
