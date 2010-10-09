#include "logic/network/events/eventcodec.h"

#include <cstring>
#include <boost/uuid/string_generator.hpp>
#include <boost/lexical_cast.hpp>

#include "logic/network/events/event.h"
#include "logic/network/events/loginevent.h"
#include "logic/network/events/logoffevent.h"
#include "logic/network/events/attackevent.h"
#include "logic/network/events/takeevent.h"
#include "logic/network/events/dropevent.h"
#include "logic/network/events/equipevent.h"
#include "logic/network/events/useevent.h"
#include "logic/network/events/moveevent.h"

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
      char bytes[16];
      memcpy(bytes, (char *)code + sizeof(EventTypes), sizeof(bytes));
      boost::uuids::string_generator gen;
      boost::uuids::uuid source(gen(std::string(bytes)));
      Position position = *(Position *)((char *)code + sizeof(EventTypes) + 
                          sizeof(source.data));
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

void EventCodec::Visit(LoginEvent &login_event) {

}

void EventCodec::Visit(LogoffEvent &logoff_event) {

}

void EventCodec::Visit(AttackEvent &attack_event) {

}

void EventCodec::Visit(MoveEvent &move_event) {
  boost::uuids::uuid id = move_event.source();
  Position move = move_event.move();
  EventTypes type = kMoveEvent;

  coded_event_ = new char [kCodeSize];
  memset(coded_event_, 0, kCodeSize);
  
  memcpy(coded_event_, &type, sizeof(type));
  memcpy((char *)coded_event_ + sizeof(kMoveEvent), id.data, sizeof(id.data));
  memcpy((char *)coded_event_ + sizeof(kMoveEvent) + sizeof(id.data), 
         &move, sizeof(move));
}

void EventCodec::Visit(TakeEvent &take_event) {

}

void EventCodec::Visit(DropEvent &drop_event) {

}

void EventCodec::Visit(EquipEvent &equip_event) {

}

void EventCodec::Visit(UseEvent &use_event) {

}

}  // namespace impdungeon

