#ifndef IMPDUNGEON_LOGIC_NETWORK_EVENTS_PLAYEREVENT_H_
#define IMPDUNGEON_LOGIC_NETWORK_EVENTS_PLAYEREVENT_H_

#include "logic/network/events/event.h"

#include <boost/uuid/uuid.hpp>

namespace impdungeon {

class PlayerEvent : public Event {
 public:
  PlayerEvent(boost::uuids::uuid &source);
  virtual ~PlayerEvent();

  virtual void Accept(EventVisitorInterface &event_visitor) = 0;

  boost::uuids::uuid source() const;

 private:
  boost::uuids::uuid source_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_EVENTS_PLAYEREVENT_H_

