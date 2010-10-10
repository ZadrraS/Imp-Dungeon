#ifndef IMPDUNGEON_LOGIC_NETWORK_EVENTS_EVENTCODEC_H_
#define IMPDUNGEON_LOGIC_NETWORK_EVENTS_EVENTCODEC_H_

#include <stdint.h>
#include <string>

#include "logic/network/events/event.h"
#include "logic/network/events/eventvisitorinterface.h"

#include <boost/uuid/uuid.hpp>

namespace impdungeon {

class EventCodec : public EventVisitorInterface {
 public:
  static const int kCodeSize = 256;

  EventCodec();
  virtual ~EventCodec();

  char *Encode(Event &event);
  Event *Decode(char *code);

 private:
  enum EventTypes {
    kNotAnEvent,
    kLoginEvent,
    kLogoffEvent,
    kAttackEvent,
    kMoveEvent,
    kTakeEvent,
    kDropEvent,
    kEquipEvent,
    kUseEvent
  };

  EventTypes ExtractType(char *data, size_t &offset);
  int ExtractInt(char *data, size_t &offset);
  std::string ExtractString(char *data, size_t &offset);
  boost::uuids::uuid ExtractUuid(char *data, size_t &offset);

  // Inherited from the EventVisitorInterface
  void Visit(LoginEvent &login_event);
  void Visit(LogoffEvent &logoff_event);
  void Visit(AttackEvent &attack_event);
  void Visit(MoveEvent &move_event);
  void Visit(TakeEvent &take_event);
  void Visit(DropEvent &drop_event);
  void Visit(EquipEvent &equip_event);
  void Visit(UseEvent &use_event);

  void InsertType(EventTypes event_type, size_t &offset);
  void InsertInt(int value, size_t &offset);
  void InsertString(const std::string &string, size_t &offset);
  void InsertUuid(const boost::uuids::uuid &id, size_t &offset);

  char *coded_event_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_EVENTS_EVENTCODEC_H_

