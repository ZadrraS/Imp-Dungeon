#ifndef IMPDUNGEON_LOGIC_NETWORK_EVENTS_DROPEVENT_H_
#define IMPDUNGEON_LOGIC_NETWORK_EVENTS_DROPEVENT_H_

#include "logic/network/events/targetedplayerevent.h"

namespace impdungeon {

class DropEvent : public TargetedPlayerEvent {
 public:
  DropEvent(boost::uuids::uuid &source, boost::uuids::uuid &target);
  virtual ~DropEvent();

  void Accept(EventVisitorInterface &event_visitor);
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_EVENTS_DROPEVENT_H_
