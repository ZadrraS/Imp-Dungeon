#ifndef IMPDUNGEON_NETWORK_EVENTS_MOVEEVENT_H_
#define IMPDUNGEON_NETWORK_EVENTS_MOVEEVENT_H_

#include "network/events/event.h"
#include "map/attributes/position.h"

namespace impdungeon {

class MoveEvent {
 public:
  MoveEvent(Position &move);
  virtual ~MoveEvent(); 

  void Accept(EventVisitorInterface *event_visitor);

  Position move() const;

 private:
  Position move_;
};

}  // namespace events

#endif  // IMPDUNGEON_NETWORK_EVENTS_MOVEEVENT_H_

