#include "logic/network/events/eventcodec.h"

#include <cstring>

#include "logic/network/events/moveevent.h"

namespace impdungeon {

EventCodec::EventCodec() {

}

EventCodec::~EventCodec() {

}

uint8_t *EventCodec::Encode(Event &event) {
  event.Accept(*this);

  return coded_event_;
}

Event *EventCodec::Decode(uint8_t *code) {
  EventTypes event_type = ((EventTypes *)code)[0];
  Event *event;  

  // TODO(ZadrraS): All event types have to be coded in.
  switch (event_type) {
    case kMoveEvent: {
      event = (MoveEvent *)((EventTypes *)code + 1);
      break;
    }    
    default: {
      event = NULL;
      break;
    }
  }
  return event;
}

void EventCodec::Visit(MoveEvent &move_event) {
  coded_event_ = new uint8_t [sizeof(EventTypes) + sizeof(move_event)];
  ((EventTypes *)coded_event_)[0] = kMoveEvent;
  memcpy((int *)coded_event_ + 1, &move_event, sizeof(move_event));
}

}  // namespace impdungeon

