#ifndef IMPDUNGEON_ENTITY_H_
#define IMPDUNGEON_ENTITY_H_

#include <string>

#include <boost/uuid/uuid.hpp>

#include "bounded_attribute.h"

namespace impdungeon {

/*-------------------
* An entity represents a moving and interacting parts of the world.
* This class is not supposed to be instantiated directly - see EntityManager.
---------------------*/
class Entity {
  public:
    Entity(const boost::uuids::uuid &id, const std::string &name, const BoundedAttribute &health);
    virtual ~Entity();

    void Damage(int amount);

    boost::uuids::uuid id() const;
    std::string name() const;
    BoundedAttribute health() const;

  private:
    boost::uuids::uuid id_;

    std::string name_;
    BoundedAttribute health_;

};

}  // namespace impdungeon

#endif  // IMPDUNGEON_ENTITY_H_

