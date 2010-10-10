#include "logic/network/events/eventcodec.h"

#include <cstring>
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
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
#include <iostream>
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
  size_t offset = 0; 
  
  EventTypes event_type = ExtractType(code, offset);
  Event *event;

  switch (event_type) {  
    case kLoginEvent: {
      std::string user_name = ExtractString(code, offset);
      std::string password = ExtractString(code, offset);

      event = new LoginEvent(user_name, password);
      break;
    }
    case kLogoffEvent: {
      boost::uuids::uuid source = ExtractUuid(code, offset);
      
      event = new LogoffEvent(source);
      break;
    }
    case kAttackEvent: {
      boost::uuids::uuid source = ExtractUuid(code, offset);
      boost::uuids::uuid target = ExtractUuid(code, offset);

      event = new AttackEvent(source, target);
      break;
    }
    case kMoveEvent: {
      boost::uuids::uuid source = ExtractUuid(code, offset);
      int x = ExtractInt(code, offset);
      int y = ExtractInt(code, offset);
      Position position(x, y);

      event = new MoveEvent(source, position);
      break;
    }
    case kTakeEvent: {
      boost::uuids::uuid source = ExtractUuid(code, offset);
      boost::uuids::uuid target = ExtractUuid(code, offset);

      event = new AttackEvent(source, target);    
      break;
    }
    case kDropEvent: {
      boost::uuids::uuid source = ExtractUuid(code, offset);
      boost::uuids::uuid target = ExtractUuid(code, offset);

      event = new AttackEvent(source, target);
      break;
    }
    case kEquipEvent: {
      boost::uuids::uuid source = ExtractUuid(code, offset);
      boost::uuids::uuid target = ExtractUuid(code, offset);

      event = new AttackEvent(source, target);
      break;
    }
    case kUseEvent: {
      boost::uuids::uuid source = ExtractUuid(code, offset);
      boost::uuids::uuid target = ExtractUuid(code, offset);

      event = new AttackEvent(source, target);
      break;
    }
    default: {
      event = NULL;
      break;
    }
  }
  return event;
}

EventCodec::EventTypes EventCodec::ExtractType(char *data, size_t &offset) {
  EventTypes event_type;
  memcpy(&event_type, data + offset, sizeof(EventTypes));
  offset += sizeof(EventTypes);

  return event_type;
}

int EventCodec::ExtractInt(char *data, size_t &offset) {
  int result;
  memcpy(&result, data + offset, sizeof(result));
  offset += sizeof(result);

  return result;
}

std::string EventCodec::ExtractString(char *data, size_t &offset) {
  int string_size;
  char *c_string;

  memcpy(&string_size, data + offset, sizeof(string_size));
  c_string = new char [string_size];
  offset += sizeof(string_size);
  memcpy(c_string, data + offset, string_size);
  offset += string_size;

  return std::string(c_string);
}

boost::uuids::uuid EventCodec::ExtractUuid(char *data, size_t &offset) {
  char id_str[36];
  memcpy(id_str, data + offset, sizeof(id_str));
  boost::uuids::string_generator gen;
  boost::uuids::uuid id(gen(std::string(id_str)));
  offset += sizeof(id_str);

  return id;
}

void EventCodec::Visit(LoginEvent &login_event) {
  coded_event_ = new char [kCodeSize];
  memset(coded_event_, 0, kCodeSize);
  size_t offset = 0;

  // Structure: [EventTypes - 1int][size - 1int][std::string - size][size - 1int][std::string - size]
  InsertType(kLoginEvent, offset);
  InsertString(login_event.user_name(), offset);
  InsertString(login_event.password(), offset);
}

void EventCodec::Visit(LogoffEvent &logoff_event) {
  coded_event_ = new char [kCodeSize];
  memset(coded_event_, 0, kCodeSize);
  size_t offset = 0;

  InsertType(kLogoffEvent, offset);
  InsertUuid(logoff_event.source(), offset);
}

void EventCodec::Visit(AttackEvent &attack_event) {
  coded_event_ = new char [kCodeSize];
  memset(coded_event_, 0, kCodeSize);
  size_t offset = 0;

  InsertType(kAttackEvent, offset);
  InsertUuid(attack_event.source(), offset);
  InsertUuid(attack_event.target(), offset);
}

void EventCodec::Visit(MoveEvent &move_event) {
  coded_event_ = new char [kCodeSize];
  memset(coded_event_, 0, kCodeSize);
  size_t offset = 0;
  
  // Structure: [EventTypes - 1int][UUID - 36char][Position - 2int]
  InsertType(kMoveEvent, offset);
  InsertUuid(move_event.source(), offset);
  int x, y;
  x = move_event.move().x();
  y = move_event.move().y();
  memcpy(coded_event_ + offset, &x, sizeof(x));
  offset += sizeof(x);
  memcpy(coded_event_ + offset, &y, sizeof(y));
  offset += sizeof(y);
}

void EventCodec::Visit(TakeEvent &take_event) {
  coded_event_ = new char [kCodeSize];
  memset(coded_event_, 0, kCodeSize);
  size_t offset = 0;

  InsertType(kTakeEvent, offset);
  InsertUuid(take_event.source(), offset);
  InsertUuid(take_event.target(), offset);
}

void EventCodec::Visit(DropEvent &drop_event) {
  coded_event_ = new char [kCodeSize];
  memset(coded_event_, 0, kCodeSize);
  size_t offset = 0;

  InsertType(kDropEvent, offset);
  InsertUuid(drop_event.source(), offset);
  InsertUuid(drop_event.target(), offset);
}

void EventCodec::Visit(EquipEvent &equip_event) {
  coded_event_ = new char [kCodeSize];
  memset(coded_event_, 0, kCodeSize);
  size_t offset = 0;

  InsertType(kEquipEvent, offset);
  InsertUuid(equip_event.source(), offset);
  InsertUuid(equip_event.target(), offset);
}

void EventCodec::Visit(UseEvent &use_event) {
  coded_event_ = new char [kCodeSize];
  memset(coded_event_, 0, kCodeSize);
  size_t offset = 0;

  InsertType(kUseEvent, offset);
  InsertUuid(use_event.source(), offset);
  InsertUuid(use_event.target(), offset);
}

void EventCodec::InsertType(EventTypes event_type, size_t &offset) {
  memcpy(coded_event_ + offset, &event_type, sizeof(event_type));

  offset += sizeof(EventTypes);
}

void EventCodec::InsertInt(int value, size_t &offset) {
  memcpy(coded_event_ + offset, &value, sizeof(value));
  offset += sizeof(value);
}

void EventCodec::InsertString(const std::string &string, size_t &offset) {
  int string_size = string.size() + 1; 
  memcpy(coded_event_ + offset, &string_size, sizeof(string_size));
  offset += sizeof(string_size);
  memcpy(coded_event_ + offset, string.c_str(), string_size);
  offset += string_size;
}

void EventCodec::InsertUuid(const boost::uuids::uuid &id, size_t &offset) {
  std::string id_str = boost::lexical_cast<std::string>(id);
  
  memcpy(coded_event_ + offset, id_str.c_str(), id_str.size());
  offset += id_str.size();
}


}  // namespace impdungeon

