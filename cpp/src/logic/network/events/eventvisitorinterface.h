#ifndef IMPDUNGEON_LOGIC_NETWORK_EVENTS_EVENTVISITORINTERFACE_H_
#define IMPDUNGEON_LOGIC_NETWORK_EVENTS_EVENTVISITORINTERFACE_H_

namespace impdungeon {

class MoveEvent;

class EventVisitorInterface {
 public:
  virtual void Visit(MoveEvent &move_event) = 0;
};

}  // namespace events

#endif  // IMPDUNGEON_LOGIC_NETWORK_EVENTS_EVENTVISITORINTERFACE_H_

