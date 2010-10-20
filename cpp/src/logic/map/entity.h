#ifndef IMPDUNGEON_LOGIC_MAP_ENTITY_H_
#define IMPDUNGEON_LOGIC_MAP_ENTITY_H_

#include <string>

#include <boost/uuid/uuid.hpp>

#include "logic/map/attributes/boundedattribute.h"
#include "logic/map/inventory.h"

namespace impdungeon {

class Weapon;

/*-------------------
* An entity represents a moving and interacting parts of the world.
* This class is not supposed to be instantiated directly - see EntityManager.
---------------------*/
class Entity {
 public:
  Entity(const std::string &name, const BoundedAttribute &health);
  virtual ~Entity();

  void Damage(int amount);
  void Heal(int amount);

  void EquipWeapon(const Weapon *weapon);
  void TakeItem(Item *item);

  // Assigns an id to an entity. This can be done only once.
  // Returns false if the entity already has an id attached.
  bool AssignId(const boost::uuids::uuid &id);

  boost::uuids::uuid id() const;
  std::string name() const;
  BoundedAttribute health() const;
  const Weapon *weapon() const;

 private:
  boost::uuids::uuid id_;

  std::string name_;
  BoundedAttribute health_;
  Inventory inventory_;

  const Weapon *weapon_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_MAP_ENTITY_H_

