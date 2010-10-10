#ifndef IMPDUNGEON_LOGIC_NETWORK_EVENTS_TARGETEDPLAYEREVENT_H_
#define IMPDUNGEON_LOGIC_NETWORK_EVENTS_TARGETEDPLAYEREVENT_H_

#include "logic/network/events/playerevent.h"

#include <boost/uuid/uuid.hpp>

namespace impdungeon {

class TargetedPlayerEvent : public PlayerEvent {
 public:
  TargetedPlayerEvent(boost::uuids::uuid &source, boost::uuids::uuid &target);
  virtual ~TargetedPlayerEvent();

  virtual void Accept(EventVisitorInterface &event_visitor) = 0;

  boost::uuids::uuid target() const;

 private:
  boost::uuids::uuid target_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_EVENTS_TARGETEDPLAYEREVENT_H_

