#ifndef IMPDUNGEON_WORLD_H_
#define IMPDUNGEON_WORLD_H_

#include <vector>
#include <queue>

#include <boost/unordered_map.hpp>

#include "map.h"
#include "entitymanager.h"

namespace impdungeon {

class Entity;
class Event;

class World {
  public:
    World();
    virtual ~World();

    void Init();
    void Run();

  private:
    Map map_;
    boost::unordered_map<Entity *, Position> entities_;
    EntityManager entity_manager_;

    std::queue <Event *> events_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_WORLD_H_

