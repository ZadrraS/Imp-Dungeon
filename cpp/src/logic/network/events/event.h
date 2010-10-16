#ifndef IMPDUNGEON_LOGIC_NETWORK_EVENTS_EVENT_H_
#define IMPDUNGEON_LOGIC_NETWORK_EVENTS_EVENT_H_

namespace impdungeon {

class EventVisitorInterface;

class Event {
 public:
  Event();
  virtual ~Event();

  virtual void Accept(EventVisitorInterface &event_visitor) = 0;

  void set_descriptor(int descriptor);
  int descriptor() const;

 private:
  int descriptor_;
};

}  // namespace events

#endif  // IMPDUNGEON_LOGIC_NETWORK_EVENTS_EVENT_H_

