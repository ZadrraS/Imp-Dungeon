#ifndef IMPDUNGEON_LOGIC_NETWORK_EVENTS_LOGOFFEVENT_H_
#define IMPDUNGEON_LOGIC_NETWORK_EVENTS_LOGOFFEVENT_H_

#include "logic/network/events/playerevent.h"

namespace impdungeon {

class LogoffEvent : public PlayerEvent {
 public:
  LogoffEvent(boost::uuids::uuid &source);
  virtual ~LogoffEvent();

  void Accept(EventVisitorInterface &event_visitor);
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_EVENTS_LOGOFFEVENT_H_
