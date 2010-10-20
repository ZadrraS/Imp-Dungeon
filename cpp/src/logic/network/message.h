#ifndef IMPDUNGEON_LOGIC_NETWORK_MESSAGE_H_
#define IMPDUNGEON_LOGIC_NETWORK_MESSAGE_H_

#include <string>

#include <boost/uuid/uuid.hpp>

namespace impdungeon {

class Entity;
class Item;
class Position;
class View;

class Message {
 public:
  static const int kMaxBufferSize = 2048;

  enum MessageType {
    kInvalidMessage,
    kEmptyMessage,
    kErrorMessage,
    kEntityDataMessage,
    kItemDataMessage,
    kViewUpdateMessage
  };

  Message(MessageType message_type);
  explicit Message(char *buffer);
  Message(const Message &message);
  virtual ~Message();
  
  Message &operator=(const Message &message);
  

  Entity *ExtractEntity();
  Item *ExtractItem();
  Position *ExtractPosition();
  View *ExtractView();
  bool ExtractSuccess();
  std::string ExtractError();

  void InjectEntity(const Entity &entity);
  void InjectItem(const Item &item);
  void InjectPosition(const Position &position);
  void InjectView(const View &view);
  void InjectSuccess(bool success);
  void InjectError(std::string error);

  char ExtractChar();
  int ExtractInt();
  std::string ExtractString();
  boost::uuids::uuid ExtractUuid();
  char *ExtractArray();

  void InjectChar(char value);
  void InjectInt(int value);
  void InjectString(const std::string &string);
  void InjectUuid(const boost::uuids::uuid &id);
  void InjectArray(const char *array, int size); 

  const char *buffer() const;

 private:
  MessageType ExtractMessageType();
  void InjectMessageType(MessageType message_type);

  MessageType message_type_;
  char *buffer_;
  size_t position_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_MESSAGE_H_

