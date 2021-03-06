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

#include "logic/network/events/events.h"
#include "logic/network/message.h"

#include "logic/map/view.h"

#include <iostream>

namespace impdungeon {
namespace server {

World::World(uint16_t port,
             const std::string &map_file_name, 
             const std::string &entity_file_name,
             const std::string &item_file_name) 
  : server_(port, *this), 
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
}

void World::Run() {
  running_ = true;
  while (running_) {
    server_.DispatchMessages();
    server_.Listen();
    while (!events_.empty()) {
      Event *event = events_.front();
      events_.pop();
      event->Accept(*this);
    }
  }
}

void World::PushEvent(Event *event) {
  events_.push(event);
}

void World::Visit(LoginEvent &login_event) {
  std::string user = login_event.user_name();
  if (entity_loader_->IsNameRegistered(user)) {
    Position position(entity_loader_->GetPosition(user));
    Entity *entity = new Entity(user, entity_loader_->GetHealth(user));

    std::vector<Item *> items = entity_loader_->GetItems(user);
    BOOST_FOREACH(Item *item, items) {
      item_manager_.SpawnItem(item);
      entity->TakeItem(item);
    }
    entity->EquipWeapon(entity_loader_->GetWeapon(user));
    boost::uuids::uuid entity_id = entity_manager_.SpawnEntity(entity);
    entities_[entity_id] = position;
    server_.RegisterClient(login_event.descriptor(), entity_id);

    std::cout << "Player " << login_event.user_name() 
              << " has just connected." << std::endl;

    Message *message = new Message(Message::kEntityDataMessage);
    message->InjectEntity(*entity);
    message->InjectPosition(position);
    server_.PushMessage(message, login_event.descriptor());
  }
  else {
    Message *message = new Message(Message::kErrorMessage);
    message->InjectError("User does not exist.");
    server_.PushMessage(message, login_event.descriptor());
  }
}

void World::Visit(LogoffEvent &logoff_event) {
  boost::uuids::uuid source = server_.GetClientId(logoff_event.descriptor());
  server_.DisconnectClient(logoff_event.descriptor());
  entities_.erase(source);
  entity_manager_.DespawnEntity(source);
}

void World::Visit(AttackEvent &attack_event) {

}

void World::Visit(MoveEvent &move_event) {
  typedef boost::unordered_map<boost::uuids::uuid, Position> map;
  boost::uuids::uuid source = server_.GetClientId(move_event.descriptor());

  if (entity_manager_.GetEntity(source) != NULL) {
    const Position &entity_position = entities_[source];

    bool entity_blocking = false;
    BOOST_FOREACH(map::value_type entity_value, entities_) {
        // Check if an entity other than the player is on the specified tile
        if (entity_value.second == move_event.move() &&
            entity_value.first != source) {
          entity_blocking = true;
        }
      }
    if (map_->IsPassable(move_event.move()) &&
        entity_position.IsNextTo(move_event.move()) && !entity_blocking) {
      entities_[source] = move_event.move();
      Message *message = new Message(Message::kEmptyMessage);
      server_.PushMessage(message, move_event.descriptor());
    }
    else {
      Message *message = new Message(Message::kErrorMessage);
      message->InjectError("Your path is blocked!");
      server_.PushMessage(message, move_event.descriptor());
    }
  }
  else {
    Message *message = new Message(Message::kErrorMessage);
    message->InjectError("Encountered critical error. Please restart client.");
    server_.PushMessage(message, move_event.descriptor());
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
  typedef boost::unordered_map<boost::uuids::uuid, Position> map;

  boost::uuids::uuid source = server_.GetClientId(view_update_event.descriptor());
  View *view = map_->GetView(entities_[source], 
                             view_update_event.width(), 
                             view_update_event.height());
  Message *message = new Message(Message::kViewUpdateMessage);
  message->InjectView(*view);

  int entity_count = entities_.size();
  message->InjectInt(entity_count);
  BOOST_FOREACH(map::value_type entity_value, entities_) {
    boost::uuids::uuid id = entity_value.first;
    Position position = entity_value.second;
    message->InjectUuid(id);
    message->InjectPosition(position);
  }

  int item_count = items_.size();
  message->InjectInt(item_count);
  BOOST_FOREACH(map::value_type item_value, items_) {
    boost::uuids::uuid id = item_value.first;
    Position position = item_value.second;
    message->InjectUuid(id);
    message->InjectPosition(position);
  }

  server_.PushMessage(message, view_update_event.descriptor());
  delete view;
}

}  // namespace server
}  // namespace impdungeon

