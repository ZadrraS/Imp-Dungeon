#ifndef IMPDUNGEON_NETWORK_EVENTS_EVENT_H_
#define IMPDUNGEON_NETWORK_EVENTS_EVENT_H_

#include <boost/uuid/uuid.hpp>

namespace impdungeon {

class EventVisitorInterface;

class Event {
 public:
  Event(boost::uuids::uuid &source);
  virtual ~Event();

  virtual void Accept(EventVisitorInterface &event_visitor) = 0;

  boost::uuids::uuid source() const;

 private:
  boost::uuids::uuid source_;
};

}  // namespace events

#endif  // IMPDUNGEON_NETWORK_EVENTS_EVENT_H_

