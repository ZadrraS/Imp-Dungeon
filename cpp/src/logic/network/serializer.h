#ifndef IMPDUNGEON_LOGIC_NETWORK_SERIALIZER_H_
#define IMPDUNGEON_LOGIC_NETWORK_SERIALIZER_H_

#include <stdint.h>
#include <string>

#include <boost/uuid/uuid.hpp>

#include "logic/network/events/eventvisitorinterface.h"

namespace impdungeon {

class Event;
class Message;

class Serializer : public EventVisitorInterface {
 public:
  static const int kMaxEventSize = 128;

  Serializer();
  virtual ~Serializer();

  char *SerializeEvent(Event &event);
  Event *UnserializeEvent(char *data);

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

  EventType ExtractEventType(char *data, size_t &offset);
  int ExtractInt(char *data, size_t &offset);
  std::string ExtractString(char *data, size_t &offset);
  boost::uuids::uuid ExtractUuid(char *data, size_t &offset);
  char *ExtractArray(int size, char *data, size_t &offset);

  void InsertEventType(EventType event_type, char *data, size_t &offset);
  void InsertInt(int value, char *data, size_t &offset);
  void InsertString(const std::string &string, char *data, size_t &offset);
  void InsertUuid(const boost::uuids::uuid &id, char *data, size_t &offset);
  void InsertArray(const char *array, int size, char *data, size_t &offset);

  char *storage_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_SERIALIZER_H_

