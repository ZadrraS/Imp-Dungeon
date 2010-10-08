#include "logic/loaders/maploader.h"

#include <fstream>

#include <boost/foreach.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "logic/map/map.h"
#include "logic/loaders/malformeddata.h"

namespace impdungeon {

MapLoader::MapLoader(const std::string &map_file_name, 
                     const std::string &item_file_name, 
                     const ItemLoader &item_loader) 
  : map_file_name_(map_file_name),
    item_file_name_(item_file_name), 
    item_loader_(item_loader) {

}

MapLoader::~MapLoader() {

}

void MapLoader::Init() {
  try {
    boost::property_tree::json_parser::read_json(item_file_name_, root_);
  }  
  catch(boost::property_tree::ptree_error &exception) {
    throw MalformedData("Item file \"" + item_file_name_ + "\" not found.");
  }
}

Map *MapLoader::GetMap() const {
  std::ifstream map_file(map_file_name_.c_str());
  int width, height;
  map_file >> width >> height;
  
  Tile *tiles = new Tile[width * height];
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      char tile_rep;
      map_file >> tile_rep;
      if (tile_rep == '#')
         tiles[y * width + x] = kWall;
      else if (tile_rep == '~')
        tiles[y * width + x] = kWater;
      else
        tiles[y * width + x] = kGround;

      // TODO(ZadrraS): Error checking
    }
  }
  map_file.close();

  Map *map = new Map(width, height, tiles);
  return map;
}

std::vector<ObjectData> MapLoader::GetItems() const {
  std::vector<ObjectData> items;  
  try {
    BOOST_FOREACH(const boost::property_tree::ptree::value_type &item_value,
                  root_.get_child("")) {
      ObjectData item_info;
      item_info.name = item_value.first;
      int x = root_.get<int>(item_value.first + ".position.x");
      int y = root_.get<int>(item_value.first + ".position.y");
      item_info.position = Position(x, y);

      items.push_back(item_info);
    }
  }
  catch(boost::property_tree::ptree_error &exception) {
    throw MalformedData("Map item does not match database.");
  }
  return items;
}

}  // namespace impdungeon
