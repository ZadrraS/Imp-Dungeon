#include "server/world.h"

#include <fstream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/uuid/uuid.hpp>

#include "logic/map/entity.h"
#include "logic/map/items/item.h"
#include "logic/map/attributes/position.h"
#include "logic/map/attributes/boundedattribute.h"
#include "logic/loaders/entityloader.h"
#include "logic/loaders/maploader.h"
#include "logic/loaders/itemloader.h"

#include "logic/network/events/event.h"
#include "logic/network/events/playerevent.h"
#include "logic/network/events/loginevent.h"
#include "logic/network/events/logoffevent.h"
#include "logic/network/events/attackevent.h"
#include "logic/network/events/takeevent.h"
#include "logic/network/events/dropevent.h"
#include "logic/network/events/equipevent.h"
#include "logic/network/events/useevent.h"
#include "logic/network/events/moveevent.h"
#include "logic/network/events/viewupdateevent.h"

#include <iostream>

namespace impdungeon {
namespace server {

World::World(const std::string &map_file_name, 
             const std::string &entity_file_name,
             const std::string &item_file_name) 
  : server_(50000, *this), 
    map_(NULL),
    running_(false) {
  item_loader_ = new ItemLoader(item_file_name);
  entity_loader_ = new EntityLoader(entity_file_name, *item_loader_);
  map_loader_ = new MapLoader(map_file_name + ".txt", map_file_name + ".json", 
                              *item_loader_);
}

World::~World() {
  typedef boost::unordered_map<boost::uuids::uuid, Position> position_map;
  BOOST_FOREACH(position_map::value_type &entity, entities_) {
    entity_manager_.DespawnEntity(entity.first);
  }
  BOOST_FOREACH(position_map::value_type &item, items_) {
    item_manager_.DespawnItem(item.first);
  }
  if (entity_loader_ != NULL)
    delete entity_loader_;
  if (map_loader_ != NULL)
    delete map_loader_;
  if (item_loader_ != NULL)
    delete item_loader_;
}

void World::Init() {
  item_loader_->Init();
  entity_loader_->Init();
  map_loader_->Init();

  server_.Init();

  // TODO(ZadrraS): Possibly move all item loading logic somewhere else.
  map_ = map_loader_->GetMap();
  std::vector<ObjectData> object_data = map_loader_->GetItems();
  BOOST_FOREACH(ObjectData &object, object_data) {
    Item *item = item_loader_->GetItem(object.name);
    boost::uuids::uuid item_id = item_manager_.SpawnItem(item);
    items_[item_id] = object.position;    
  } 

  // TODO(ZadrraS): Possibly move all entity loading logic somewhere else.
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
  running_ = true;
  while (running_) {
    server_.Listen();
    while (!events_.empty()) {
      Event *event = events_.front();
      event->Accept(*this);
      events_.pop();
    }
  }
}

void World::PushEvent(Event *event) {
  events_.push(event);
}

void World::Visit(LoginEvent &login_event) {
  std::cout << "Katik prisijunge " << login_event.user_name() 
            << " su slaptazodziu " << login_event.password() << "." << std::endl;
}

void World::Visit(LogoffEvent &logoff_event) {

}

void World::Visit(AttackEvent &attack_event) {

}

void World::Visit(MoveEvent &move_event) {
  if (entity_manager_.GetEntity(move_event.source()) != NULL) {
    const Position &entity_position = entities_[move_event.source()];
    if (map_->IsPassable(move_event.move()) && 
        entity_position.IsNextTo(move_event.move())) {
      entities_[move_event.source()] = move_event.move();
    }
  }
}

void World::Visit(TakeEvent &take_event) {

}

void World::Visit(DropEvent &drop_event) {

}

void World::Visit(EquipEvent &equip_event) {

}

void World::Visit(UseEvent &use_event) {

}

void World::Visit(ViewUpdateEvent &view_update_event) {

}

}  // namespace server
}  // namespace impdungeon

