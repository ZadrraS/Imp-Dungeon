#ifndef IMPDUNGEON_LOGIC_NETWORK_EVENTS_MOVEEVENT_H_
#define IMPDUNGEON_LOGIC_NETWORK_EVENTS_MOVEEVENT_H_

#include "logic/network/events/event.h"
#include "logic/map/attributes/position.h"

namespace impdungeon {

class MoveEvent : public Event {
 public:
  MoveEvent(boost::uuids::uuid &source, Position &move);
  virtual ~MoveEvent(); 

  void Accept(EventVisitorInterface &event_visitor);

  Position move() const;

 private:
  Position move_;
};

}  // namespace events

#endif  // IMPDUNGEON_LOGIC_NETWORK_EVENTS_MOVEEVENT_H_

