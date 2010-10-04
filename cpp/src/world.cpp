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
#include "loaders/entityloader.h"
#include "loaders/maploader.h"
#include "loaders/itemloader.h"

namespace impdungeon {

World::World(const std::string &map_file_name, 
             const std::string &entity_file_name,
             const std::string &item_file_name) : map_(NULL) {
  item_loader_ = new ItemLoader(item_file_name);
  entity_loader_ = new EntityLoader(entity_file_name, *item_loader_);
  map_loader_ = new MapLoader(map_file_name + ".txt", map_file_name + ".json", 
                              *item_loader_);
}

World::~World() {

}

void World::Init() {
  item_loader_->Init();
  entity_loader_->Init();
  map_loader_->Init();

  // TODO(ZadrraS): Possibly move all item loading logic somewhere else.
  map_ = map_loader_->GetMap();
  std::vector<ObjectData> object_data = map_loader_->GetItems();
  BOOST_FOREACH(ObjectData &object, object_data) {
    Item *item = item_loader_->GetItem(object.name);
    boost::uuids::uuid item_id = item_manager_.SpawnItem(item);
    items_[item_id] = object.position;    
  } 

  // TODO(ZadrraS): Move all entity loading logic somewhere else.
  Position position(entity_loader_->GetPosition("ZadrraS"));
  Entity *entity = new Entity("ZadrraS", entity_loader_->GetHealth("ZadrraS"));

  std::vector<Item *> items = entity_loader_->GetItems("ZadrraS");
  BOOST_FOREACH(Item *item, items) {
    item_manager_.SpawnItem(item);
    entity->TakeItem(item);  
  }

  boost::uuids::uuid entity_id = entity_manager_.SpawnEntity(entity);
  entities_[entity_id] = position;


}

void World::Run() {

}

void World::Destroy() {
  typedef boost::unordered_map<boost::uuids::uuid, Position> position_map;
  BOOST_FOREACH(position_map::value_type &entity, entities_) {
    entity_manager_.DespawnEntity(entity.first);
  }
  BOOST_FOREACH(position_map::value_type &item, items_) {
    item_manager_.DespawnItem(item.first);
  }
  delete entity_loader_;
  delete map_loader_;
  delete item_loader_;
}

}  // namespace impdungeon

