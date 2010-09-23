#ifndef IMPDUNGEON_ENTITYMANAGER_H_
#define IMPDUNGEON_ENTITYMANAGER_H_

#include <boost/unordered_map.hpp>

namespace impdungeon {

/*-------------------
* An Entity factory and manager, enabling entities to be created, destroyed
* and accessed. Entities are indexed and refered to by their unique id's.
---------------------*/
class EntityManager {
  public:
    EntityFactory();
    virtual ~EntityFactory();

    boost::uuids::uuid &GenerateEntity(std::string &name, BoundedAttribute &health);
    void DestroyEntity(boost::uuids::uuid &id);

    Entity *entity(boost::uuids::uuid &id) const;

  private:
    boost::unordered_map<boost::uuids::uuid, Entity *> entities_;

};

}  // namespace impdungeon

#endif  // IMPDUNGEON_ENTITYMANAGER_H_

