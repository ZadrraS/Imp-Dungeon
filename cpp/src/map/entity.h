#ifndef IMPDUNGEON_MAP_ENTITY_H_
#define IMPDUNGEON_MAP_ENTITY_H_

#include <string>

#include <boost/uuid/uuid.hpp>

#include "map/attributes/boundedattribute.h"

namespace impdungeon {

/*-------------------
* An entity represents a moving and interacting parts of the world.
* This class is not supposed to be instantiated directly - see EntityManager.
---------------------*/
class Entity {
 public:
  Entity(const std::string &name, const BoundedAttribute &health);
  virtual ~Entity();

  void Damage(int amount);

  // Assigns an id to an entity. This can be done only once.
  // Returns false if the entity already has an id attached.
  bool AssignId(const boost::uuids::uuid &id);

  boost::uuids::uuid id() const;
  std::string name() const;
  BoundedAttribute health() const;

 private:
  boost::uuids::uuid id_;

  std::string name_;
  BoundedAttribute health_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_MAP_ENTITY_H_

