#include "loaders/entityloader.h"

#include <boost/foreach.hpp>

#include "map/entity.h"
#include "map/items/item.h"
#include "map/items/weapon.h"
#include "map/items/potion.h"

namespace impdungeon {

EntityLoader::EntityLoader() {

}

EntityLoader::~EntityLoader() {

}

std::string EntityLoader::GetPassword(const std::string &name) {
  return root().get<std::string>(name + ".password");
}

std::string EntityLoader::GetMap(const std::string &name) {
  return root().get<std::string>(name + ".map");
}

Position EntityLoader::GetPosition(const std::string &name) {
  int x, y;
  x = root().get<int>(name + ".position.x");
  y = root().get<int>(name + ".position.y");

  return Position(x, y);
}  

BoundedAttribute EntityLoader::GetHealth(const std::string &name) {
  int current, max;
  current = root().get<int>(name + ".health.current");
  max = root().get<int>(name + ".health.max");

  return BoundedAttribute(current, max);
}

std::vector<Item *> EntityLoader::GetItems(const std::string &name) {
  std::vector<Item *> items;  
  BOOST_FOREACH(const boost::property_tree::ptree::value_type &item_value, 
                root().get_child(name + ".inventory")) {
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
