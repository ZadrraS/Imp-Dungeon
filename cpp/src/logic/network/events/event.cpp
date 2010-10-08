#include "logic/network/events/event.h"

namespace impdungeon {

Event::Event(boost::uuids::uuid &source) : source_(source) {

}

Event::~Event() {

}

boost::uuids::uuid Event::source() const {
  return source_;
}

}  // namespace events

