#include "map/inventory.h"

#include <boost/foreach.hpp>

#include "map/items/item.h"

namespace impdungeon {

Inventory::Inventory(std::vector<Item *> &items) : items_(items) {

}

Inventory::Inventory() {

}

Inventory::~Inventory() {

}

void Inventory::AddItem(Item *item) {
  items_.push_back(item);
}

bool Inventory::RemoveItem(boost::uuids::uuid &id) {
  for (std::vector<Item *>::iterator it = items_.begin(); it != items_.end(); it++) {
    if ((*it)->id() == id) {
      items_.erase(it);
      return true;
    }
  }
  return false;
}

Item *Inventory::GetItem(boost::uuids::uuid &id) {
  BOOST_FOREACH(Item *item, items_) {
    if (item->id() == id) {
      return item;
    }
  }
  return NULL;
}

std::vector<Item *>::iterator Inventory::begin() {
  return items_.begin();
}

std::vector<Item *>::iterator Inventory::end() {
  return items_.end();
}

}  // namespace impdungeon
