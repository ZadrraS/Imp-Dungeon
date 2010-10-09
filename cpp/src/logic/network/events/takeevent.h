#ifndef IMPDUNGEON_LOGIC_NETWORK_EVENTS_TAKEEVENT_H_
#define IMPDUNGEON_LOGIC_NETWORK_EVENTS_TAKEEVENT_H_

#include "logic/network/events/event.h"

namespace impdungeon {

class TakeEvent : public Event {
 public:
  TakeEvent(boost::uuids::uuid &source, boost::uuids::uuid &target);
  virtual ~TakeEvent();

  void Accept(EventVisitorInterface &event_visitor);

 private:
  boost::uuids::uuid target_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_EVENTS_TAKEEVENT_H_
