#ifndef IMPDUNGEON_LOGIC_NETWORK_EVENTS_TARGETEDEVENT_H_
#define IMPDUNGEON_LOGIC_NETWORK_EVENTS_TARGETEDEVENT_H_

#include "logic/network/events/event.h"

#include <boost/uuid/uuid.hpp>

namespace impdungeon {

class TargetedEvent : public Event {
 public:
  TargetedEvent(boost::uuids::uuid &target);
  virtual ~TargetedEvent();

  virtual void Accept(EventVisitorInterface &event_visitor) = 0;

  boost::uuids::uuid target() const;

 private:
  boost::uuids::uuid target_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_EVENTS_TARGETEDEVENT_H_

