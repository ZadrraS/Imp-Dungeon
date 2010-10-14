#include "logic/network/serializer.h"

#include <cstring>
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>

#include "logic/network/events/events.h"

#include "logic/network/messages/messages.h"

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
      boost::uuids::uuid source = ExtractUuid(data, offset);
      
      event = new LogoffEvent(source);
      break;
    }
    case kAttackEvent: {
      boost::uuids::uuid source = ExtractUuid(data, offset);
      boost::uuids::uuid target = ExtractUuid(data, offset);

      event = new AttackEvent(source, target);
      break;
    }
    case kMoveEvent: {
      boost::uuids::uuid source = ExtractUuid(data, offset);
      int x = ExtractInt(data, offset);
      int y = ExtractInt(data, offset);
      Position position(x, y);

      event = new MoveEvent(source, position);
      break;
    }
    case kTakeEvent: {
      boost::uuids::uuid source = ExtractUuid(data, offset);
      boost::uuids::uuid target = ExtractUuid(data, offset);

      event = new AttackEvent(source, target);    
      break;
    }
    case kDropEvent: {
      boost::uuids::uuid source = ExtractUuid(data, offset);
      boost::uuids::uuid target = ExtractUuid(data, offset);

      event = new AttackEvent(source, target);
      break;
    }
    case kEquipEvent: {
      boost::uuids::uuid source = ExtractUuid(data, offset);
      boost::uuids::uuid target = ExtractUuid(data, offset);

      event = new AttackEvent(source, target);
      break;
    }
    case kUseEvent: {
      boost::uuids::uuid source = ExtractUuid(data, offset);
      boost::uuids::uuid target = ExtractUuid(data, offset);

      event = new AttackEvent(source, target);
      break;
    }
    case kViewUpdateEvent: {
      boost::uuids::uuid source = ExtractUuid(data, offset);
      int width = ExtractInt(data, offset);
      int height = ExtractInt(data, offset);
      event = new ViewUpdateEvent(source, width, height);
      break;
    }
    default: {
      event = NULL;
      break;
    }
  }
  return event;
}

char *Serializer::SerializeMessage(Message &message) {
  message.Accept(*this);

  return storage_;
}

Message *Serializer::UnserializeMessage(char *data) {
  size_t offset = 0; 
  MessageType message_type = ExtractMessageType(data, offset);
  Message *message;
  switch (message_type) {
    case kErrorMessage: {
      std::string msg = ExtractString(data, offset);

      message = new ErrorMessage(msg);
      break;
    }
    case kEntityDataMessage: {
      boost::uuids::uuid source = ExtractUuid(data, offset);
      std::string name = ExtractString(data, offset);
      int health_value = ExtractInt(data, offset);
      int health_bound = ExtractInt(data, offset);
      BoundedAttribute health(health_value, health_bound);

      Entity *entity = new Entity(name, health);
      entity->AssignId(source);

      message = new EntityDataMessage(entity);
      break;
    }
    case kViewUpdateMessage: {
      int width = ExtractInt(data, offset);
      int height = ExtractInt(data, offset);
      char *view_data = ExtractArray(width*height, data, offset);
      View *view = new View(view_data, width, height);
      message = new ViewUpdateMessage(view);
      break;
    }
    default: {
      message = NULL;
      break;
    }
    // TODO(ZadrraS): Code in all other message parsing.
  }
  return message;
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
  InsertUuid(logoff_event.source(), storage_, offset);
}

void Serializer::Visit(AttackEvent &attack_event) {
  storage_ = new char [kMaxEventSize];
  memset(storage_, 0, kMaxEventSize);
  size_t offset = 0;

  InsertEventType(kAttackEvent, storage_, offset);
  InsertUuid(attack_event.source(), storage_, offset);
  InsertUuid(attack_event.target(), storage_, offset);
}

void Serializer::Visit(MoveEvent &move_event) {
  storage_ = new char [kMaxEventSize];
  memset(storage_, 0, kMaxEventSize);
  size_t offset = 0;
  
  // Structure: [EventTypes - 1int][UUID - 36char][Position - 2int]
  InsertEventType(kMoveEvent, storage_, offset);
  InsertUuid(move_event.source(), storage_, offset);
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
  InsertUuid(take_event.source(), storage_, offset);
  InsertUuid(take_event.target(), storage_, offset);
}

void Serializer::Visit(DropEvent &drop_event) {
  storage_ = new char [kMaxEventSize];
  memset(storage_, 0, kMaxEventSize);
  size_t offset = 0;

  InsertEventType(kDropEvent, storage_, offset);
  InsertUuid(drop_event.source(), storage_, offset);
  InsertUuid(drop_event.target(), storage_, offset);
}

void Serializer::Visit(EquipEvent &equip_event) {
  storage_ = new char [kMaxEventSize];
  memset(storage_, 0, kMaxEventSize);
  size_t offset = 0;

  InsertEventType(kEquipEvent, storage_, offset);
  InsertUuid(equip_event.source(), storage_, offset);
  InsertUuid(equip_event.target(), storage_, offset);
}

void Serializer::Visit(UseEvent &use_event) {
  storage_ = new char [kMaxEventSize];
  memset(storage_, 0, kMaxEventSize);
  size_t offset = 0;

  InsertEventType(kUseEvent, storage_, offset);
  InsertUuid(use_event.source(), storage_, offset);
  InsertUuid(use_event.target(), storage_, offset);
}

void Serializer::Visit(ViewUpdateEvent &view_update_event) {
  storage_ = new char [kMaxEventSize];
  memset(storage_, 0, kMaxEventSize);
  size_t offset = 0;

  InsertEventType(kViewUpdateEvent, storage_, offset);
  InsertUuid(view_update_event.source(), storage_, offset);
  InsertInt(view_update_event.width(), storage_, offset);
  InsertInt(view_update_event.height(), storage_, offset);
}

void Serializer::Visit(ErrorMessage &error_message) {
  storage_ = new char [kMaxMessageSize];
  memset(storage_, 0, kMaxMessageSize);
  size_t offset = 0;

  InsertMessageType(kErrorMessage, storage_, offset);
  InsertString(error_message.message(), storage_, offset);
}

void Serializer::Visit(EntityDataMessage &entity_data_message) {
  storage_ = new char [kMaxMessageSize];
  memset(storage_, 0, kMaxMessageSize);
  size_t offset = 0;

  Entity *entity = entity_data_message.entity();
  InsertMessageType(kEntityDataMessage, storage_, offset);
  InsertUuid(entity->id(), storage_, offset);
  InsertString(entity->name(), storage_, offset);
  InsertInt(entity->health().value(), storage_, offset);
  InsertInt(entity->health().bound(), storage_, offset);
  // TODO(ZadrraS): Finish entity data message serialization.
}

void Serializer::Visit(ItemDataMessage &item_data_message) {
  storage_ = new char [kMaxMessageSize];
  memset(storage_, 0, kMaxMessageSize);
  size_t offset = 0;

  InsertMessageType(kItemDataMessage, storage_, offset);
  // TODO(ZadrraS): Finish item data message serialization.
}

void Serializer::Visit(ViewUpdateMessage &view_update_message) {
  storage_ = new char [kMaxMessageSize];
  memset(storage_, 0, kMaxMessageSize);
  size_t offset = 0;
  InsertMessageType(kViewUpdateMessage, storage_, offset);
  InsertInt(view_update_message.view()->width(), storage_, offset);
  InsertInt(view_update_message.view()->height(), storage_, offset); 
  InsertArray(view_update_message.view()->tiles(), 
              view_update_message.view()->width() * 
              view_update_message.view()->height(), 
              storage_, offset);
}

Serializer::EventType Serializer::ExtractEventType(char *data, size_t &offset) {
  EventType event_type;
  memcpy(&event_type, data + offset, sizeof(EventType));
  offset += sizeof(EventType);

  return event_type;
}

Serializer::MessageType Serializer::ExtractMessageType(char *data, 
                                                       size_t &offset) {
  MessageType message_type;
  memcpy(&message_type, data + offset, sizeof(MessageType));
  offset += sizeof(MessageType);

  return message_type;
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

void Serializer::InsertMessageType(MessageType message_type, char *data, size_t &offset) {
  memcpy(data + offset, &message_type, sizeof(MessageType));

  offset += sizeof(MessageType);
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

