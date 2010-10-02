#include "world.h"

#include <fstream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/uuid/uuid.hpp>

#include "map/entity.h"
#include "map/items/item.h"
#include "map/attributes/position.h"
#include "map/attributes/boundedattribute.h"

namespace impdungeon {

World::World() : map_(NULL) {

}

World::~World() {

}

void World::Init(const std::string &map_file_name, 
                 const std::string &entity_file_name) {
  entity_loader_.Init(entity_file_name, "items.json", map_file_name);

  map_ = entity_loader_.GetMap();
  // TODO(ZadrraS): Move all entity loading logic somewhere else.
  Position *position = new Position(entity_loader_.GetEntityPosition("ZadrraS"));
  Entity *entity = new Entity("ZadrraS", entity_loader_.GetEntityHealth("ZadrraS"));

  std::vector<Item *> items = entity_loader_.GetEntityItems("ZadrraS");
  BOOST_FOREACH(Item *item, items) {
    item_manager_.SpawnItem(item);
    entity->TakeItem(item);  
  }

  boost::uuids::uuid id = entity_manager_.SpawnEntity(entity);
  entities_[id] = position;


}

void World::Run() {

}

void World::Destroy() {
  typedef boost::unordered_map<boost::uuids::uuid, Position *> position_map;
  BOOST_FOREACH(position_map::value_type entity, entities_) {
    entity_manager_.DespawnEntity(entity.first);
    delete entity.second;
  }
  BOOST_FOREACH(position_map::value_type item, items_) {
    item_manager_.DespawnItem(item.first);
    delete item.second;
  }
}

}  // namespace impdungeon

