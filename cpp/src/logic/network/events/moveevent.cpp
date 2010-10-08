#include "logic/network/events/moveevent.h"

#include "logic/network/events/eventvisitorinterface.h"

namespace impdungeon {

MoveEvent::MoveEvent(boost::uuids::uuid &source, Position &move) 
  : Event(source),
    move_(move) {

}

MoveEvent::~MoveEvent() {

}

void MoveEvent::Accept(EventVisitorInterface &event_visitor) {
  event_visitor.Visit(*this);
}

Position MoveEvent::move() const {
  return move_;
}

}  // namespace events

