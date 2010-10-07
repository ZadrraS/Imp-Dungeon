#include "network/events/eventcodec.h"

#include <cstring>

#include "network/events/moveevent.h"

namespace impdungeon {

EventCodec::EventCodec() {

}

EventCodec::~EventCodec() {

}

char *EventCodec::Encode(Event &event) {
  event.Accept(*this);

  return coded_event_;
}

Event *EventCodec::Decode(char *code) {
  EventTypes event_type = ((EventTypes *)code)[0];
  Event *event;  

  // TODO(ZadrraS): All event types have to be coded in.
  switch (event_type) {
    case kMoveEvent: {
      
      boost::uuids::uuid source = *(boost::uuids::uuid *)((char *)code + sizeof(EventTypes));
      Position position = *(Position *)((char *)code + sizeof(EventTypes) + 
                          sizeof(boost::uuids::uuid));
      event = new MoveEvent(source, position);
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
  coded_event_ = new char [sizeof(EventTypes) + sizeof(move_event)];
  ((EventTypes *)coded_event_)[0] = kMoveEvent;
  memcpy((EventTypes *)coded_event_ + 1, &move_event, sizeof(move_event));
}

}  // namespace impdungeon

