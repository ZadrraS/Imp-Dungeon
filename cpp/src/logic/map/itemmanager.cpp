#include "logic/map/itemmanager.h"

#include "logic/map/items/item.h"

namespace impdungeon {

ItemManager::ItemManager() {

}

ItemManager::~ItemManager() {

}

const boost::uuids::uuid ItemManager::SpawnItem(Item *item) {
  if (item->id().is_nil()) {
    item->AssignId(uuid_generator_());
    items_[item->id()] = item;
  }

  return item->id();
}

void ItemManager::DespawnItem(const boost::uuids::uuid &id) {
  delete items_[id];
  items_.erase(id);
  // TODO(ZadrraS): Make this not explode in your face when handed a bad id.
}

Item *ItemManager::GetItem(const boost::uuids::uuid &id) {
  return items_[id];
  // TODO(ZadrraS): Make this return NULL if a bad id is passed.
}

}  // namespace impdungeon
