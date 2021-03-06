#include "logic/network/events/viewupdateevent.h"

#include "logic/network/events/eventvisitorinterface.h"

namespace impdungeon {

ViewUpdateEvent::ViewUpdateEvent(int width, int height) 
  : width_(width), height_(height) {

}

ViewUpdateEvent::~ViewUpdateEvent() {

}

void ViewUpdateEvent::Accept(EventVisitorInterface &event_visitor) {
  event_visitor.Visit(*this);
}

int ViewUpdateEvent::width() const {
  return width_;
}

int ViewUpdateEvent::height() const {
  return height_;
}

}  // namespace impdungeon
