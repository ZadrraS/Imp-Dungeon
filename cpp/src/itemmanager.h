#ifndef IMPDUNGEON_ITEMMANAGER_H_
#define IMPDUNGEON_ITEMMANAGER_H_

#include <boost/unordered_map.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include "item.h"

namespace impdungeon {

/*-------------------
* An Item manager, enabling items to be registered in the game, destroyed 
* and accessed. Items are indexed and refered to by their unique id's.
---------------------*/
class ItemManager {
 public:
  ItemManager();
  virtual ~ItemManager();

  // Registers an item in the system and assigns it an unique id.
  const boost::uuids::uuid SpawnItem(Item *item);
  // Removes a registered item from the system and deletes it.
  void DespawnItem(const boost::uuids::uuid &id);

  Item *item(const boost::uuids::uuid &id);

 private:
  boost::unordered_map<boost::uuids::uuid, Item *> items_;

  boost::uuids::random_generator uuid_generator_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_ITEMMANAGER_H_
