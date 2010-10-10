#include "logic/network/events/playerevent.h"

namespace impdungeon {

PlayerEvent::PlayerEvent(boost::uuids::uuid &source) : source_(source) {

}

PlayerEvent::~PlayerEvent() {

}

boost::uuids::uuid PlayerEvent::source() const {
  return source_;
}

}  // namespace impdungeon
