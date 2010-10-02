#include "loader.h"

#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include "map/attributes/boundedattribute.h"
#include "map/entity.h"
#include "map/items/item.h"
#include "map/items/weapon.h"
#include "map/items/potion.h"

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
    Item *item;
    switch (item_value.second.get<char>("type")) {
      case 'w':
        item = new Weapon(item_value.first, 
                          item_value.second.get<int>("value"),
                          item_value.second.get<int>("min_damage"),
                          item_value.second.get<int>("max_damage"));
      break;
      case 'p':
        item = new Potion(item_value.first,
                          item_value.second.get<int>("value"),
                          item_value.second.get<int>("strength"));
      break;
    }
    items.push_back(item);
  }

  return items;
}

}  // namespace impdungeon

