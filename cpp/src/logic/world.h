#ifndef IMPDUNGEON_LOGIC_WORLD_H_
#define IMPDUNGEON_LOGIC_WORLD_H_

#include <vector>
#include <queue>

#include <boost/unordered_map.hpp>

#include "logic/map/map.h"
#include "logic/map/entitymanager.h"
#include "logic/map/itemmanager.h"
#include "logic/network/events/eventvisitorinterface.h"

namespace impdungeon {

class Entity;
class Event;
class EntityLoader;
class MapLoader;
class ItemLoader;

/*-------------------
* World manages received events and ties together most of the games subsystems.
---------------------*/
class World : public EventVisitorInterface {
 public:
  World(const std::string &map_file_name, 
        const std::string &entity_file_name,
        const std::string &item_file_name);
  virtual ~World();

  void Init();
  void Run();

  void PushEvent(Event *event);

  // Inherited from the EventVisitorInterface
  void Visit(MoveEvent &move_event);

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

