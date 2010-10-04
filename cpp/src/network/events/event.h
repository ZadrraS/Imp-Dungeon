#ifndef IMPDUNGEON_NETWORK_EVENTS_EVENT_H_
#define IMPDUNGEON_NETWORK_EVENTS_EVENT_H_

namespace impdungeon {

class EventVisitorInterface;

class Event {
 public:
  Event();
  virtual ~Event();

  virtual void Accept(EventVisitorInterface *event_visitor) = 0;
};

}  // namespace events

#endif  // IMPDUNGEON_NETWORK_EVENTS_EVENT_H_

