#include "logic/network/events/logoffevent.h"

#include "logic/network/events/eventvisitorinterface.h"

namespace impdungeon {

LogoffEvent::LogoffEvent() {

}

LogoffEvent::~LogoffEvent() {

}

void LogoffEvent::Accept(EventVisitorInterface &event_visitor) {
  event_visitor.Visit(*this);
}

}  // namespace impdungeon
