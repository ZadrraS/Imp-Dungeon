#ifndef IMPDUNGEON_LOGIC_NETWORK_EVENTS_EVENTCODEC_H_
#define IMPDUNGEON_LOGIC_NETWORK_EVENTS_EVENTCODEC_H_

#include <stdint.h>

#include "logic/network/events/event.h"
#include "logic/network/events/eventvisitorinterface.h"

namespace impdungeon {

class EventCodec : public EventVisitorInterface {
 public:
  static const int kCodeSize = 256;

  EventCodec();
  virtual ~EventCodec();

  char *Encode(Event &event);
  Event *Decode(char *code);

  // Inherited from the EventVisitorInterface
  void Visit(MoveEvent &move_event);

 private:
  enum EventTypes {
    kMoveEvent
  };

  char *coded_event_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_EVENTS_EVENTCODEC_H_

