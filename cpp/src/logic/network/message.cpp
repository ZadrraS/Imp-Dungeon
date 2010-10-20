#include "logic/network/message.h"

#include <cstring>

#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/string_generator.hpp>

#include "logic/map/entity.h"
#include "logic/map/items/item.h"
#include "logic/map/items/weapon.h"
#include "logic/map/attributes/position.h"
#include "logic/map/view.h"

namespace impdungeon {

Message::Message(MessageType message_type) 
  : message_type_(message_type),
    buffer_(new char [kMaxBufferSize]), 
    position_(0) {
  memset(buffer_, 0, kMaxBufferSize);
  InjectMessageType(message_type);
}

Message::Message(char *buffer)
  : message_type_(kInvalidMessage),
    buffer_(buffer),
    position_(0) {
  if (buffer_)
    message_type_ = ExtractMessageType();
}

Message::Message(const Message &message) {
  message_type_ = message.message_type_;
  position_ = message.position_;

  if (buffer_)
    delete [] buffer_;
  memcpy(buffer_, message.buffer_, kMaxBufferSize);
}

Message::~Message() {
  if (buffer_)
    delete [] buffer_;
}

Message &Message::operator=(const Message &message) {
  if (buffer_)
    delete [] buffer_;
  memcpy(buffer_, message.buffer_, kMaxBufferSize);

  return *this;
}

Entity *Message::ExtractEntity() {
  if (message_type_ == kEntityDataMessage ||
      message_type_ == kViewUpdateMessage) {
    boost::uuids::uuid source = ExtractUuid();
    std::string name = ExtractString();
    int health_value = ExtractInt();
    int health_bound = ExtractInt();
    BoundedAttribute health(health_value, health_bound);

    Entity *entity = new Entity(name, health);
    entity->AssignId(source);

    std::string weapon_name = ExtractString();
    int value = ExtractInt();
    int min_damage = ExtractInt();
    int max_damage = ExtractInt();
    Weapon *weapon = new Weapon(weapon_name, value, min_damage, max_damage);
    weapon->Equip(*entity);

    return entity;
  }

  return NULL;
}

Item *Message::ExtractItem() {
  // TODO(ZadrraS): Item extraction
  return NULL;
}

Position *Message::ExtractPosition() {
  int x = ExtractInt();
  int y = ExtractInt();
  Position *position = new Position(x, y);

  return position;
}

View *Message::ExtractView() {
  if (message_type_ == kViewUpdateMessage) {
    int width = ExtractInt();
    int height = ExtractInt();
    char *view_data = ExtractArray();
    int pos_x = ExtractInt();
    int pos_y = ExtractInt();
    View *view = new View(view_data, width, height, Position(pos_x, pos_y));

    return view;
  }

  return NULL;
}

bool Message::ExtractSuccess() {
  if (message_type_ == kInvalidMessage || message_type_ == kErrorMessage)
    return false;

  return true;
}

std::string Message::ExtractError() {
  return ExtractString();
}

void Message::InjectEntity(const Entity &entity) {
  InjectUuid(entity.id());
  InjectString(entity.name());
  InjectInt(entity.health().value());
  InjectInt(entity.health().bound());
  InjectString(entity.weapon()->name());
  InjectInt(entity.weapon()->value());
  InjectInt(entity.weapon()->min_damage());
  InjectInt(entity.weapon()->max_damage());
}

void Message::InjectItem(const Item &item) {
  // TODO(ZadrraS): Item injection
}

void Message::InjectPosition(const Position &position) {
  InjectInt(position.x());
  InjectInt(position.y());
}

void Message::InjectView(const View &view) {
  InjectInt(view.width());
  InjectInt(view.height());
  InjectArray(view.tiles(), view.width()*view.height());
  InjectInt(view.position().x());
  InjectInt(view.position().y());
}

void Message::InjectSuccess(bool success) {
  InjectInt(success);
}

void Message::InjectError(std::string error) {
  InjectString(error);
}

const char *Message::buffer() const {
  return buffer_;
}

Message::MessageType Message::ExtractMessageType() {
  MessageType message_type;
  memcpy(&message_type, buffer_ + position_, sizeof(MessageType));
  position_ += sizeof(MessageType);

  return message_type;
}

char Message::ExtractChar() {
  char result;
  memcpy(&result, buffer_ + position_, sizeof(result));
  position_ += sizeof(result);

  return result;
}

int Message::ExtractInt() {
  int result;
  memcpy(&result, buffer_ + position_, sizeof(result));
  position_ += sizeof(result);

  return result;
}

std::string Message::ExtractString() {
  int string_size;

  string_size = 0;
  while (buffer_[position_ + string_size] != '\0')
    string_size++;
  string_size++;
  char c_string[string_size];
  memcpy(c_string, buffer_ + position_, string_size);
  position_ += string_size;
  return std::string(c_string);
}

boost::uuids::uuid Message::ExtractUuid() {
  char id_str[37];
  memcpy(id_str, buffer_ + position_, sizeof(id_str) - 1);
  id_str[36] = '\0';
  boost::uuids::string_generator gen;
  boost::uuids::uuid id(gen(std::string(id_str)));
  position_ += sizeof(id_str) - 1;

  return id;
}

char *Message::ExtractArray() {
  int size = ExtractInt();
  char *array = new char [size];
  memcpy(array, buffer_ + position_, size);
  position_ += size;

  return array;
}

void Message::InjectMessageType(MessageType message_type) {
  memcpy(buffer_ + position_, &message_type, sizeof(MessageType));
  position_ += sizeof(MessageType);
}

void Message::InjectChar(char value) {
  memcpy(buffer_ + position_, &value, sizeof(value));
  position_ += sizeof(value);
}

void Message::InjectInt(int value) {
  memcpy(buffer_ + position_, &value, sizeof(value));
  position_ += sizeof(value);
}

void Message::InjectString(const std::string &string) {
  int string_size = string.size() + 1; 
  memcpy(buffer_ + position_, string.c_str(), string_size);
  position_ += string_size;
}

void Message::InjectUuid(const boost::uuids::uuid &id) {
  std::string id_str = boost::lexical_cast<std::string>(id);
  memcpy(buffer_ + position_, id_str.c_str(), id_str.size());
  position_ += id_str.size();
}

void Message::InjectArray(const char *array, int size) {
  InjectInt(size);
  memcpy(buffer_ + position_, array, size);
  position_ += size;
}

}  // namespace impdungeon

