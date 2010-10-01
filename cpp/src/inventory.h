#ifndef IMPDUNGEON_INVENTORY_H_
#define IMPDUNGEON_INVENTORY_H_

#include <vector>

#include <boost/uuid/uuid.hpp>

namespace impdungeon {

class Item;

/*-------------------
* Inventory stores Items allowing convenient access to them by their id's and
* iteration using BOOST_FOREACH.
---------------------*/
class Inventory {
 public:
  Inventory();
  virtual ~Inventory();

  void AddItem(Item *item);

  // Removes an item by its id from the inventory. 
  // Returns false if unsuccsessful.
  bool RemoveItem(boost::uuids::uuid &id);

  // Returns an item by its id.
  // If an item specified is not in the inventory false is returned.
  Item *item(boost::uuids::uuid &id);

  std::vector<Item *>::iterator begin();
  std::vector<Item *>::iterator end();
  typedef std::vector<Item *>::iterator iterator;
  typedef std::vector<Item *>::const_iterator const_iterator;

 private:
  std::vector<Item *> items_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_INVENTORY_H_
