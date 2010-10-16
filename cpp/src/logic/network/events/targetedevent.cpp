#include "logic/network/events/targetedevent.h"

namespace impdungeon {

TargetedEvent::TargetedEvent(boost::uuids::uuid &target) : target_(target) {

}

TargetedEvent::~TargetedEvent() {

}

boost::uuids::uuid TargetedEvent::target() const {
  return target_;
}

}  // namespace impdungeon

