#ifndef IMPDUNGEON_WORLD_H_
#define IMPDUNGEON_WORLD_H_

#include <vector>
#include <queue>

#include <boost/unordered_map.hpp>

#include "map.h"
#include "entitymanager.h"
#include "itemmanager.h"
#include "loader.h"

namespace impdungeon {

class Entity;
class Event;


/*-------------------
* World manages received events and ties together most of the games subsystems.
---------------------*/
class World {
 public:
  World();
  virtual ~World();

  void Init(const std::string &map_file_name, 
            const std::string &entity_file_name);
  void Run();
  void Destroy();

 private:
  Map map_;
  boost::unordered_map<boost::uuids::uuid, Position *> entities_;
  boost::unordered_map<boost::uuids::uuid, Position *> items_;

  EntityManager entity_manager_;
  ItemManager item_manager_;
  Loader loader_;

  std::queue <Event *> events_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_WORLD_H_

