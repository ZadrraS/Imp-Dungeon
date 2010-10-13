#ifndef IMPDUNGEON_LOGIC_NETWORK_EVENTS_VIEWUPDATEEVENT_H_
#define IMPDUNGEON_LOGIC_NETWORK_EVENTS_VIEWUPDATEEVENT_H_

#include "logic/network/events/playerevent.h"

namespace impdungeon {

class ViewUpdateEvent : public PlayerEvent {
 public:
  ViewUpdateEvent(boost::uuids::uuid &source);
  virtual ~ViewUpdateEvent();

  void Accept(EventVisitorInterface &event_visitor);
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_EVENTS_VIEWUPDATEEVENT_H_
