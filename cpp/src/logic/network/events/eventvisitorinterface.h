#ifndef IMPDUNGEON_LOGIC_NETWORK_EVENTS_EVENTVISITORINTERFACE_H_
#define IMPDUNGEON_LOGIC_NETWORK_EVENTS_EVENTVISITORINTERFACE_H_

namespace impdungeon {

class LoginEvent;
class LogoffEvent;
class AttackEvent;
class MoveEvent;
class TakeEvent;
class DropEvent;
class EquipEvent;
class UseEvent;

class EventVisitorInterface {
 public:
  virtual void Visit(LoginEvent &login_event) = 0;
  virtual void Visit(LogoffEvent &logoff_event) = 0;
  virtual void Visit(AttackEvent &attack_event) = 0;
  virtual void Visit(MoveEvent &move_event) = 0;
  virtual void Visit(TakeEvent &take_event) = 0;
  virtual void Visit(DropEvent &drop_event) = 0;
  virtual void Visit(EquipEvent &equip_event) = 0;
  virtual void Visit(UseEvent &use_event) = 0;
};

}  // namespace events

#endif  // IMPDUNGEON_LOGIC_NETWORK_EVENTS_EVENTVISITORINTERFACE_H_

