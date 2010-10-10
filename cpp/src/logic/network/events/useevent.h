#ifndef IMPDUNGEON_LOGIC_NETWORK_EVENTS_USEEVENT_H_
#define IMPDUNGEON_LOGIC_NETWORK_EVENTS_USEEVENT_H_

#include "logic/network/events/targetedplayerevent.h"

namespace impdungeon {

class UseEvent : public TargetedPlayerEvent {
 public:
  UseEvent(boost::uuids::uuid &source, boost::uuids::uuid &target);
  virtual ~UseEvent();

  void Accept(EventVisitorInterface &event_visitor);
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_EVENTS_USEEVENT_H_
