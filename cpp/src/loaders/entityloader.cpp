#include "loaders/entityloader.h"

#include <boost/foreach.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "map/entity.h"
#include "map/items/item.h"
#include "map/items/weapon.h"
#include "map/items/potion.h"
#include "loaders/malformeddata.h"
#include "map/map.h"

namespace impdungeon {

EntityLoader::EntityLoader() {

}

EntityLoader::~EntityLoader() {

}

void EntityLoader::Init(const std::string &file_name, 
                        const std::string &item_file_name, 
                        const std::string &map_name) {
  try {
    Loader::Init(file_name);
    boost::property_tree::json_parser::read_json(item_file_name, item_database_);
    boost::property_tree::json_parser::read_json(map_name + ".json", map_root_);
    map_name_ = map_name;
  }
  catch(boost::property_tree::ptree_error &exception) {
    throw MalformedData("Data files not found");
  }
}

std::string EntityLoader::GetEntityPassword(const std::string &name) {
  try {
    return root().get<std::string>(name + ".password");
  }
  catch(boost::property_tree::ptree_error &exception) {
    throw MalformedData("Entity password data malformed.");
  }
}

std::string EntityLoader::GetEntityMap(const std::string &name) {
  try {
    return root().get<std::string>(name + ".map");
  }
  catch(boost::property_tree::ptree_error &exception) {
    throw MalformedData("Entity map name data malformed.");
  }
}

Position EntityLoader::GetEntityPosition(const std::string &name) {
  int x, y;
  try {
    x = root().get<int>(name + ".position.x");
    y = root().get<int>(name + ".position.y");
  }
  catch(boost::property_tree::ptree_error &exception) {
    throw MalformedData("Entity position data malformed.");
  }

  return Position(x, y);
}  

BoundedAttribute EntityLoader::GetEntityHealth(const std::string &name) {
  int current, max;
  try {
    current = root().get<int>(name + ".health.current");
    max = root().get<int>(name + ".health.max");
  }
  catch(boost::property_tree::ptree_error &exception) {
    throw MalformedData("Entity health data malformed.");
  }
  return BoundedAttribute(current, max);
}

std::vector<Item *> EntityLoader::GetEntityItems(const std::string &name) {
  std::vector<Item *> items;  

  try {
    BOOST_FOREACH(const boost::property_tree::ptree::value_type &item_value,
                  root().get_child(name + ".inventory")) {

      items.push_back(ConstructItem(item_value.second.get<std::string>("")));
    }
  }
  catch(boost::property_tree::ptree_error &exception) {
    throw MalformedData("Entity inventory does not match database.");
  }

  return items;
}

Map *EntityLoader::GetMap() {
  std::ifstream map_file((map_name_ + ".txt").c_str());
  int width, height;
  map_file >> width >> height;
  
  Tile *tiles = new Tile[width * height];
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      char tile_rep;
      map_file >> tile_rep;
      if (tile_rep == '#')
         tiles[y * width + x] = WALL;
      else if (tile_rep == '~')
        tiles[y * width + x] = WATER;
      else
        tiles[y * width + x] = GROUND;

      // TODO(ZadrraS): Error checking
    }
  }
  map_file.close();

  Map *map = new Map(width, height, tiles);
  return map;
}

std::vector<PositionedItem> EntityLoader::GetItems() {
  std::vector<PositionedItem> positioned_items;  
  try {
    BOOST_FOREACH(const boost::property_tree::ptree::value_type &item_value,
                  map_root_.get_child("")) {
      PositionedItem positioned_item;
      positioned_item.item = ConstructItem(item_value.first);
      int x = map_root_.get<int>(item_value.first + ".position.x");
      int y = map_root_.get<int>(item_value.first + ".position.y");
      positioned_item.position = Position(x, y);

      positioned_items.push_back(positioned_item);
    }
  }
  catch(boost::property_tree::ptree_error &exception) {
    throw MalformedData("Map item does not match database.");
  }
  return positioned_items;
}

Item *EntityLoader::ConstructItem(const std::string &name) {
  Item *item = NULL;
  try {
    const boost::property_tree::ptree &database_item = 
      item_database_.get_child(name);

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
    throw MalformedData("Entity inventory does not match database.");
  }

  return item;
}

}  // namespace impdungeon
