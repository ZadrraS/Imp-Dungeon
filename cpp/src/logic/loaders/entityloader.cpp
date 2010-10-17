#include "logic/loaders/entityloader.h"

#include <boost/foreach.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "logic/map/entity.h"
#include "logic/map/items/item.h"
#include "logic/map/items/weapon.h"
#include "logic/map/items/potion.h"
#include "logic/loaders/malformeddata.h"
#include "logic/loaders/itemloader.h"
#include "logic/map/map.h"

namespace impdungeon {

EntityLoader::EntityLoader(const std::string &file_name, 
                           const ItemLoader &item_loader) 
  : file_name_(file_name),
    item_loader_(item_loader) {

}

EntityLoader::~EntityLoader() {

}

void EntityLoader::Init() {
  try {
    boost::property_tree::json_parser::read_json(file_name_, root_);
  }
  catch(boost::property_tree::ptree_error &exception) {
    throw MalformedData("Entity file \"" + file_name_ + "\" not found.");
  }
}

bool EntityLoader::IsNameRegistered(const std::string &entity_name) const {
  if (root_.find(entity_name) == root_.not_found())
    return false;

  return true;
}

std::string EntityLoader::GetPassword(const std::string &name) const {
  try {
    return root_.get<std::string>(name + ".password");
  }
  catch(boost::property_tree::ptree_error &exception) {
    throw MalformedData("Entity password malformed.");
  }
}

std::string EntityLoader::GetMap(const std::string &name) const {
  try {
    return root_.get<std::string>(name + ".map");
  }
  catch(boost::property_tree::ptree_error &exception) {
    throw MalformedData("Entity map name malformed.");
  }
}

Position EntityLoader::GetPosition(const std::string &name) const {
  int x, y;
  try {
    x = root_.get<int>(name + ".position.x");
    y = root_.get<int>(name + ".position.y");
  }
  catch(boost::property_tree::ptree_error &exception) {
    throw MalformedData("Entity position data malformed.");
  }

  return Position(x, y);
}  

BoundedAttribute EntityLoader::GetHealth(const std::string &name) const {
  int current, max;
  try {
    current = root_.get<int>(name + ".health.current");
    max = root_.get<int>(name + ".health.max");
  }
  catch(boost::property_tree::ptree_error &exception) {
    throw MalformedData("Entity health data malformed.");
  }
  return BoundedAttribute(current, max);
}

Weapon *EntityLoader::GetWeapon(const std::string &name) const {
  std::string weapon_name;
  try {
    weapon_name = root_.get<std::string>(name + ".weapon");
  }
  catch(boost::property_tree::ptree_error &exception) {
    throw MalformedData("Entity weapon data malformed.");
  }
  return static_cast<Weapon *>(item_loader_.GetItem(weapon_name));
}

std::vector<Item *> EntityLoader::GetItems(const std::string &name) const {
  std::vector<Item *> items;

  try {
    BOOST_FOREACH(const boost::property_tree::ptree::value_type &item_value,
                  root_.get_child(name + ".inventory")) {

      items.push_back(item_loader_.GetItem(item_value.second.get<std::string>("")));
    }
  }
  catch(boost::property_tree::ptree_error &exception) {
    throw MalformedData("Entity inventory does not match database.");
  }

  return items;
}

}  // namespace impdungeon
