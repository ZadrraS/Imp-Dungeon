#ifndef IMPDUNGEON_LOGIC_NETWORK_EVENTS_LOGOFFEVENT_H_
#define IMPDUNGEON_LOGIC_NETWORK_EVENTS_LOGOFFEVENT_H_

#include "logic/network/events/event.h"

namespace impdungeon {

class LogoffEvent : public Event {
 public:
  LogoffEvent();
  virtual ~LogoffEvent();

  void Accept(EventVisitorInterface &event_visitor);
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_EVENTS_LOGOFFEVENT_H_
