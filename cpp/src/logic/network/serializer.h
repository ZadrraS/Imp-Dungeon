#ifndef IMPDUNGEON_LOGIC_NETWORK_SERIALIZER_H_
#define IMPDUNGEON_LOGIC_NETWORK_SERIALIZER_H_

#include <stdint.h>
#include <string>

#include <boost/uuid/uuid.hpp>

#include "logic/network/events/eventvisitorinterface.h"
#include "logic/network/messages/messagevisitorinterface.h"

namespace impdungeon {

class Event;
class Message;

class Serializer : public EventVisitorInterface, 
                   public MessageVisitorInterface {
 public:
  static const int kMaxEventSize = 128;
  static const int kMaxMessageSize = 1024;

  Serializer();
  virtual ~Serializer();

  char *SerializeEvent(Event &event);
  Event *UnserializeEvent(char *data);

  char *SerializeMessage(Message &message);
  Message *UnserializeMessage(char *data);

 private:
  enum EventType {
    kNotAnEvent,
    kLoginEvent,
    kLogoffEvent,
    kAttackEvent,
    kMoveEvent,
    kTakeEvent,
    kDropEvent,
    kEquipEvent,
    kUseEvent,
    kViewUpdateEvent
  };

  enum MessageType {
    kNotAMessage,
    kErrorMessage,
    kEntityDataMessage,
    kItemDataMessage,
    kViewUpdateMessage
  };

  // Inherited from EventVisitorInterface
  void Visit(LoginEvent &login_event);
  void Visit(LogoffEvent &logoff_event);
  void Visit(AttackEvent &attack_event);
  void Visit(MoveEvent &move_event);
  void Visit(TakeEvent &take_event);
  void Visit(DropEvent &drop_event);
  void Visit(EquipEvent &equip_event);
  void Visit(UseEvent &use_event);
  void Visit(ViewUpdateEvent &view_update_event);

  // Inherited from MessageVisitorInterface
  void Visit(ErrorMessage &error_message);
  void Visit(EntityDataMessage &entity_data_message);
  void Visit(ItemDataMessage &item_data_message);
  void Visit(ViewUpdateMessage &view_update_message);

  EventType ExtractEventType(char *data, size_t &offset);
  MessageType ExtractMessageType(char *data, size_t &offset);
  int ExtractInt(char *data, size_t &offset);
  std::string ExtractString(char *data, size_t &offset);
  boost::uuids::uuid ExtractUuid(char *data, size_t &offset);
  char *ExtractArray(int size, char *data, size_t &offset);

  void InsertEventType(EventType event_type, char *data, size_t &offset);
  void InsertMessageType(MessageType message_type, char *data, size_t &offset);
  void InsertInt(int value, char *data, size_t &offset);
  void InsertString(const std::string &string, char *data, size_t &offset);
  void InsertUuid(const boost::uuids::uuid &id, char *data, size_t &offset);
  void InsertArray(const char *array, int size, char *data, size_t &offset);

  char *storage_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_SERIALIZER_H_

