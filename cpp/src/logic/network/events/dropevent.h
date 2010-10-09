#ifndef IMPDUNGEON_LOGIC_NETWORK_EVENTS_DROPEVENT_H_
#define IMPDUNGEON_LOGIC_NETWORK_EVENTS_DROPEVENT_H_

#include "logic/network/events/event.h"

namespace impdungeon {

class DropEvent : public Event {
 public:
  DropEvent(boost::uuids::uuid &source, boost::uuids::uuid &target);
  virtual ~DropEvent();

  void Accept(EventVisitorInterface &event_visitor);

 private:
  boost::uuids::uuid target_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_EVENTS_DROPEVENT_H_
