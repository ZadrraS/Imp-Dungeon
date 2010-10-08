#ifndef IMPDUNGEON_LOGIC_MAP_ENTITYMANAGER_H_
#define IMPDUNGEON_LOGIC_MAP_ENTITYMANAGER_H_

#include <boost/unordered_map.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include "logic/map/attributes/boundedattribute.h"

namespace impdungeon {

class Entity;

/*-------------------
* An Entity manager, enabling entities to be registered in the game, destroyed 
* and accessed. Entities are indexed and refered to by their unique id's.
---------------------*/
class EntityManager {
 public:
  EntityManager();
  virtual ~EntityManager();

  // Registers an entity in the system and assigns it an unique id.
  const boost::uuids::uuid SpawnEntity(Entity *entity);
  // Removes a registered entity from the system and deteles it.
  void DespawnEntity(const boost::uuids::uuid &id);

  Entity *GetEntity(const boost::uuids::uuid &id);

 private:
  boost::unordered_map<boost::uuids::uuid, Entity *> entities_;

  boost::uuids::random_generator uuid_generator_;

};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_MAP_ENTITYMANAGER_H_

