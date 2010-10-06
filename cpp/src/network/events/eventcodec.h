#ifndef IMPDUNGEON_NETWORK_EVENTS_EVENTCODEC_H_
#define IMPDUNGEON_NETWORK_EVENTS_EVENTCODEC_H_

#include <stdint.h>

#include "network/events/event.h"
#include "network/events/eventvisitorinterface.h"

namespace impdungeon {

class EventCodec : public EventVisitorInterface {
 public:
  static const int kCodeSize = 256;

  EventCodec();
  virtual ~EventCodec();

  uint8_t *Encode(Event &event);
  Event *Decode(uint8_t *code);

  // Inherited from the EventVisitorInterface
  void Visit(MoveEvent &move_event);

 private:
  enum EventTypes {
    kMoveEvent
  };

  uint8_t *coded_event_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_NETWORK_EVENTS_EVENTCODEC_H_

