#ifndef IMPDUNGEON_MAP_ITEMS_ITEM_H_
#define IMPDUNGEON_MAP_ITEMS_ITEM_H_

#include <boost/uuid/uuid.hpp>

#include "map/entity.h"

namespace impdungeon {

/*-------------------
* The Item class is the base class for all items in the game.
---------------------*/
class Item {
 public:
  Item(const std::string &name, int value, bool equipable, bool usable);
  virtual ~Item();

  virtual void Equip(Entity &entity) = 0;
  virtual void Use(Entity &entity) = 0;

  // Assigns an id to an item. This can be done only once.
  // Returns false if the item already has an id attached.
  bool AssignId(const boost::uuids::uuid &id);

  const boost::uuids::uuid &id() const;
  const std::string &name() const;
  int value() const;
  bool equipable() const;
  bool usable() const;
   
 private:
  boost::uuids::uuid id_;
  std::string name_;
  int value_;

  bool equipable_;
  bool usable_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_MAP_ITEMS_ITEM_H_
