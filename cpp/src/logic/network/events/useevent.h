#ifndef IMPDUNGEON_LOGIC_NETWORK_EVENTS_USEEVENT_H_
#define IMPDUNGEON_LOGIC_NETWORK_EVENTS_USEEVENT_H_

#include "logic/network/events/event.h"

namespace impdungeon {

class UseEvent : public Event {
 public:
  UseEvent(boost::uuids::uuid &source, boost::uuids::uuid &target);
  virtual ~UseEvent();

  void Accept(EventVisitorInterface &event_visitor);

 private:
  boost::uuids::uuid target_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_EVENTS_USEEVENT_H_
