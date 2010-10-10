#include "targetedplayerevent.h"

namespace impdungeon {

TargetedPlayerEvent::TargetedPlayerEvent(boost::uuids::uuid &source, 
                                         boost::uuids::uuid &target) 
  : PlayerEvent(source), target_(target) {

}

TargetedPlayerEvent::~TargetedPlayerEvent() {

}

boost::uuids::uuid TargetedPlayerEvent::target() const {
  return target_;
}

}  // namespace impdungeon

