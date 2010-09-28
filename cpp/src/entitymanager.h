#ifndef IMPDUNGEON_ENTITYMANAGER_H_
#define IMPDUNGEON_ENTITYMANAGER_H_

#include <boost/unordered_map.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include "boundedattribute.h"

namespace impdungeon {

class Entity;

/*-------------------
* An Entity factory and manager, enabling entities to be created, destroyed
* and accessed. Entities are indexed and refered to by their unique id's.
---------------------*/
class EntityManager {
  public:
    EntityManager();
    virtual ~EntityManager();

    const boost::uuids::uuid GenerateEntity(const std::string &name, const BoundedAttribute &health);
    void DestroyEntity(const boost::uuids::uuid &id);

    Entity *entity(const boost::uuids::uuid &id);

  private:
    boost::unordered_map<boost::uuids::uuid, Entity *> entities_;

    boost::uuids::random_generator uuid_generator_;

};

}  // namespace impdungeon

#endif  // IMPDUNGEON_ENTITYMANAGER_H_

