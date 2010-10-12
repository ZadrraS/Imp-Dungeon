#ifndef IMPDUNGEON_LOGIC_WORLD_H_
#define IMPDUNGEON_LOGIC_WORLD_H_

#include <vector>
#include <queue>

#include <boost/unordered_map.hpp>

#include "logic/map/map.h"
#include "logic/map/entitymanager.h"
#include "logic/map/itemmanager.h"
#include "logic/network/events/eventvisitorinterface.h"
#include "logic/network/events/eventhandlerinterface.h"
#include "server/server.h"

namespace impdungeon {

class Entity;
class Event;
class EntityLoader;
class MapLoader;
class ItemLoader;

/*-------------------
* World manages received events and ties together most of the games subsystems.
---------------------*/
class World : public EventVisitorInterface,
              public EventHandlerInterface {
 public:
  World(const std::string &map_file_name, 
        const std::string &entity_file_name,
        const std::string &item_file_name);
  virtual ~World();

  void Init();
  void Run();

  // Inherited from EventHandlerInterface
  void PushEvent(Event *event);

  // Inherited from EventVisitorInterface
  void Visit(LoginEvent &login_event);
  void Visit(LogoffEvent &logoff_event);
  void Visit(AttackEvent &attack_event);
  void Visit(MoveEvent &move_event);
  void Visit(TakeEvent &take_event);
  void Visit(DropEvent &drop_event);
  void Visit(EquipEvent &equip_event);
  void Visit(UseEvent &use_event);

 private:
  Map *map_;
  boost::unordered_map<boost::uuids::uuid, Position> entities_;
  boost::unordered_map<boost::uuids::uuid, Position> items_;

  EntityManager entity_manager_;
  ItemManager item_manager_;

  EntityLoader *entity_loader_;
  MapLoader *map_loader_;
  ItemLoader *item_loader_;

  std::queue <Event *> events_;

};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_WORLD_H_

