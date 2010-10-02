#include "loaders/maploader.h"

#include <fstream>

#include "map/map.h"

namespace impdungeon {

MapLoader::MapLoader() {

}

MapLoader::~MapLoader() {

}

void MapLoader::Init(const std::string &map_name) {
  Loader::Init(map_name + ".json");
  map_name_ = map_name;
}

Map *MapLoader::GetMap() {
  std::ifstream map_file((map_name_ + ".txt").c_str());
  int width, height;
  map_file >> width >> height;
  
  Tile *tiles = new Tile[width * height];
  for (int y = 0; y < height_; y++) {
    for (int x = 0; x < width_; x++) {
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
  return Map(width, height, tiles);
}

std::vector<PositionedItem> MapLoader::GetItems() {
  std::vector<Item *> items;  
  try {
    BOOST_FOREACH(const boost::property_tree::ptree::value_type &item_value,
                  root().get_child(name + ".inventory")) {

      const boost::property_tree::ptree &database_item = 
        item_database_.get_child(item_value.second.get<std::string>(""));

      Item *item;
      switch (database_item.get<char>("type")) {
        case 'w': {
          item = new Weapon(item_value.second.get<std::string>(""), 
                            database_item.get<int>("value"),
                            database_item.get<int>("min_damage"),
                            database_item.get<int>("max_damage"));
          break;
        }
        case 'p': {
          item = new Potion(item_value.second.get<std::string>(""),
                            database_item.get<int>("value"),
                            database_item.get<int>("strength"));
          break;
        } 
      }
      items.push_back(item);
    }
  }
  catch(boost::property_tree::ptree_error &exception) {
    throw MalformedData("Entity inventory does not match database.");
  }

  return items;
}

}  // namespace impdungeon
