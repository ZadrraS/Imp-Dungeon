#include "logic/loaders/itemloader.h"

#include <boost/property_tree/json_parser.hpp>

#include "logic/loaders/malformeddata.h"
#include "logic/map/items/item.h"
#include "logic/map/items/weapon.h"
#include "logic/map/items/potion.h"

namespace impdungeon {

ItemLoader::ItemLoader(const std::string &file_name) : file_name_(file_name) {

}

ItemLoader::~ItemLoader() {

}

void ItemLoader::Init() {
  try {
    boost::property_tree::json_parser::read_json(file_name_, root_);
  }
  catch(boost::property_tree::ptree_error &exception) {
    throw MalformedData("Item database file \"" + file_name_ + "\" not found.");
  }
}

Item *ItemLoader::GetItem(const std::string &name) const {
  Item *item = NULL;
  try {
    const boost::property_tree::ptree &database_item = 
      root_.get_child(name);

    switch (database_item.get<char>("type")) {
      case 'w': {
        item = new Weapon(name, 
                          database_item.get<int>("value"),
                          database_item.get<int>("min_damage"),
                          database_item.get<int>("max_damage"));
        break;
      }
      case 'p': {
        item = new Potion(name,
                          database_item.get<int>("value"),
                          database_item.get<int>("strength"));
        break;
      } 
    }
  }
  catch(boost::property_tree::ptree_error &exception) {
    throw MalformedData("Item \"" + name + "\" does not match database.");
  }
  return item;
}

}  // namespace impdungeon
