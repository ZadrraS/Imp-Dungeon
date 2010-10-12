#ifndef IMPDUNGEON_LOGIC_NETWORK_EVENTS_EVENTHANDLERINTERFACE_H_
#define IMPDUNGEON_LOGIC_NETWORK_EVENTS_EVENTHANDLERINTERFACE_H_

namespace impdungeon {

class EventHandlerInterface {
 public:
  virtual void PushEvent(Event *event) = 0;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_EVENTS_EVENTHANDLERINTERFACE_H_

