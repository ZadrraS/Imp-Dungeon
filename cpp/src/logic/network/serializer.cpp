#include "logic/network/serializer.h"

#include <cstring>
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>

#include "logic/network/events/events.h"

#include "logic/network/message.h"

#include "logic/map/view.h"
#include "logic/map/entity.h"
#include "logic/map/attributes/boundedattribute.h"
#include <iostream>

namespace impdungeon {

Serializer::Serializer() {

}

Serializer::~Serializer() {

}

char *Serializer::SerializeEvent(Event &event) {
  event.Accept(*this);

  return storage_;
}

Event *Serializer::UnserializeEvent(char *data) {
  size_t offset = 0; 

  EventType event_type = ExtractEventType(data, offset);
  Event *event;

  switch (event_type) {  
    case kLoginEvent: {
      std::string user_name = ExtractString(data, offset);
      std::string password = ExtractString(data, offset);

      event = new LoginEvent(user_name, password);
      break;
    }
    case kLogoffEvent: {
      event = new LogoffEvent();
      break;
    }
    case kAttackEvent: {
      boost::uuids::uuid target = ExtractUuid(data, offset);

      event = new AttackEvent(target);
      break;
    }
    case kMoveEvent: {
      int x = ExtractInt(data, offset);
      int y = ExtractInt(data, offset);
      Position position(x, y);

      event = new MoveEvent(position);
      break;
    }
    case kTakeEvent: {
      boost::uuids::uuid target = ExtractUuid(data, offset);

      event = new AttackEvent(target);
      break;
    }
    case kDropEvent: {
      boost::uuids::uuid target = ExtractUuid(data, offset);

      event = new AttackEvent(target);
      break;
    }
    case kEquipEvent: {
      boost::uuids::uuid target = ExtractUuid(data, offset);

      event = new AttackEvent(target);
      break;
    }
    case kUseEvent: {
      boost::uuids::uuid target = ExtractUuid(data, offset);

      event = new AttackEvent(target);
      break;
    }
    case kViewUpdateEvent: {
      int width = ExtractInt(data, offset);
      int height = ExtractInt(data, offset);
      event = new ViewUpdateEvent(width, height);
      break;
    }
    default: {
      event = NULL;
      break;
    }
  }
  return event;
}

void Serializer::Visit(LoginEvent &login_event) {
  storage_ = new char [kMaxEventSize];
  memset(storage_, 0, kMaxEventSize);
  size_t offset = 0;

  // Structure: [EventTypes - 1int][size - 1int][std::string - size][size - 1int][std::string - size]
  InsertEventType(kLoginEvent, storage_, offset);
  InsertString(login_event.user_name(), storage_, offset);
  InsertString(login_event.password(), storage_, offset);
}

void Serializer::Visit(LogoffEvent &logoff_event) {
  storage_ = new char [kMaxEventSize];
  memset(storage_, 0, kMaxEventSize);
  size_t offset = 0;

  InsertEventType(kLogoffEvent, storage_, offset);
}

void Serializer::Visit(AttackEvent &attack_event) {
  storage_ = new char [kMaxEventSize];
  memset(storage_, 0, kMaxEventSize);
  size_t offset = 0;

  InsertEventType(kAttackEvent, storage_, offset);
  InsertUuid(attack_event.target(), storage_, offset);
}

void Serializer::Visit(MoveEvent &move_event) {
  storage_ = new char [kMaxEventSize];
  memset(storage_, 0, kMaxEventSize);
  size_t offset = 0;
  
  // Structure: [EventTypes - 1int][UUID - 36char][Position - 2int]
  InsertEventType(kMoveEvent, storage_, offset);
  int x, y;
  x = move_event.move().x();
  y = move_event.move().y();
  memcpy(storage_ + offset, &x, sizeof(x));
  offset += sizeof(x);
  memcpy(storage_ + offset, &y, sizeof(y));
  offset += sizeof(y);
}

void Serializer::Visit(TakeEvent &take_event) {
  storage_ = new char [kMaxEventSize];
  memset(storage_, 0, kMaxEventSize);
  size_t offset = 0;

  InsertEventType(kTakeEvent, storage_, offset);
  InsertUuid(take_event.target(), storage_, offset);
}

void Serializer::Visit(DropEvent &drop_event) {
  storage_ = new char [kMaxEventSize];
  memset(storage_, 0, kMaxEventSize);
  size_t offset = 0;

  InsertEventType(kDropEvent, storage_, offset);
  InsertUuid(drop_event.target(), storage_, offset);
}

void Serializer::Visit(EquipEvent &equip_event) {
  storage_ = new char [kMaxEventSize];
  memset(storage_, 0, kMaxEventSize);
  size_t offset = 0;

  InsertEventType(kEquipEvent, storage_, offset);
  InsertUuid(equip_event.target(), storage_, offset);
}

void Serializer::Visit(UseEvent &use_event) {
  storage_ = new char [kMaxEventSize];
  memset(storage_, 0, kMaxEventSize);
  size_t offset = 0;

  InsertEventType(kUseEvent, storage_, offset);
  InsertUuid(use_event.target(), storage_, offset);
}

void Serializer::Visit(ViewUpdateEvent &view_update_event) {
  storage_ = new char [kMaxEventSize];
  memset(storage_, 0, kMaxEventSize);
  size_t offset = 0;

  InsertEventType(kViewUpdateEvent, storage_, offset);
  InsertInt(view_update_event.width(), storage_, offset);
  InsertInt(view_update_event.height(), storage_, offset);
}

Serializer::EventType Serializer::ExtractEventType(char *data, size_t &offset) {
  EventType event_type;
  memcpy(&event_type, data + offset, sizeof(EventType));
  offset += sizeof(EventType);

  return event_type;
}

int Serializer::ExtractInt(char *data, size_t &offset) {
  int result;
  memcpy(&result, data + offset, sizeof(result));
  offset += sizeof(result);

  return result;
}

std::string Serializer::ExtractString(char *data, size_t &offset) {
  int string_size;
  char *c_string;

  memcpy(&string_size, data + offset, sizeof(string_size));
  c_string = new char [string_size];
  offset += sizeof(string_size);
  memcpy(c_string, data + offset, string_size);
  offset += string_size;

  return std::string(c_string);
}

boost::uuids::uuid Serializer::ExtractUuid(char *data, size_t &offset) {
  char id_str[36];
  memcpy(id_str, data + offset, sizeof(id_str));
  boost::uuids::string_generator gen;
  boost::uuids::uuid id(gen(std::string(id_str)));
  offset += sizeof(id_str);

  return id;
}

char *Serializer::ExtractArray(int size, char *data, size_t &offset) {
  char *array = new char [size];
  memcpy(array, data + offset, size);
  offset += size;

  return array;
}

void Serializer::InsertEventType(EventType event_type, char *data, size_t &offset) {
  memcpy(data + offset, &event_type, sizeof(EventType));

  offset += sizeof(EventType);
}

void Serializer::InsertInt(int value, char *data, size_t &offset) {
  memcpy(data + offset, &value, sizeof(value));
  offset += sizeof(value);
}

void Serializer::InsertString(const std::string &string, 
                              char *data, size_t &offset) {
  int string_size = string.size() + 1; 
  memcpy(data + offset, &string_size, sizeof(string_size));
  offset += sizeof(string_size);
  memcpy(data + offset, string.c_str(), string_size);
  offset += string_size;
}

void Serializer::InsertUuid(const boost::uuids::uuid &id, 
                            char *data, size_t &offset) {
  std::string id_str = boost::lexical_cast<std::string>(id);
  
  memcpy(data + offset, id_str.c_str(), id_str.size());
  offset += id_str.size();
}

void Serializer::InsertArray(const char *array, int size, char *data, size_t &offset) {
  memcpy(data + offset, array, size);
  offset += size;
}

}  // namespace impdungeon

