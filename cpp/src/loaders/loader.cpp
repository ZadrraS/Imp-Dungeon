#include "loader.h"

#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include "map/attributes/boundedattribute.h"
#include "map/entity.h"
#include "map/items/item.h"

namespace impdungeon {

Loader::Loader() {
  
}

Loader::~Loader() {

}

void Loader::Init(const std::string &file_name) {
  boost::property_tree::json_parser::read_json(file_name, root_);
}

std::string Loader::GetEntityPassword(const std::string &name) {
  return root_.get<std::string>(name + ".password");
}

std::string Loader::GetEntityMap(const std::string &name) {
  return root_.get<std::string>(name + ".map");
}

Position Loader::GetEntityPosition(const std::string &name) {
  int x, y;
  x = root_.get<int>(name + ".position.x");
  y = root_.get<int>(name + ".position.y");

  return Position(x, y);
}  

BoundedAttribute Loader::GetEntityHealth(const std::string &name) {
  int current, max;
  current = root_.get<int>(name + ".health.current");
  max = root_.get<int>(name + ".health.max");

  return BoundedAttribute(current, max);
}

std::vector<Item *> Loader::GetEntityItems(const std::string &name) {
  std::vector<Item *> items;  
  BOOST_FOREACH(boost::property_tree::ptree::value_type &item_value, 
                root_.get_child(name + ".inventory")) {
    // TODO(ZadrraS): All the item loading.
    switch (item_value.second.get<char>("type")) {
      case 'w':

      break;
      case 'p':

      break;
    }
  }

  return items;
  /*

  BOOST_FOREACH(boost::property_tree::ptree::value_type &value, root.get_child("")) {
    boost::property_tree::ptree health;
    health = value.second.get_child("health");

    std::cout << health.get<int>("current") << std::endl;
    Entity *entity = new Entity(
      value.first, 
      BoundedAttribute(health.get<int>("current"), health.get<int>("max")));

    Position *position = new Position(2, 2);
    entities_[entity] = position;
  
  }*/
}

}  // namespace impdungeon

