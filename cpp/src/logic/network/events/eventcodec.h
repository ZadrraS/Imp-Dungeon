#ifndef IMPDUNGEON_LOGIC_NETWORK_EVENTS_EVENTCODEC_H_
#define IMPDUNGEON_LOGIC_NETWORK_EVENTS_EVENTCODEC_H_

#include <stdint.h>

#include "logic/network/events/event.h"
#include "logic/network/events/eventvisitorinterface.h"

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
    kMoveEvent
  };

  // Inherited from the EventVisitorInterface
  void Visit(LoginEvent &login_event);
  void Visit(LogoffEvent &logoff_event);
  void Visit(AttackEvent &attack_event);
  void Visit(MoveEvent &move_event);
  void Visit(TakeEvent &take_event);
  void Visit(DropEvent &drop_event);
  void Visit(EquipEvent &equip_event);
  void Visit(UseEvent &use_event);

  char *coded_event_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_EVENTS_EVENTCODEC_H_

