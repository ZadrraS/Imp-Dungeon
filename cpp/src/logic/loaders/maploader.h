#ifndef IMPDUNGEON_LOGIC_MAP_LOADERS_MAPLOADER_H_
#define IMPDUNGEON_LOGIC_MAP_LOADERS_MAPLOADER_H_

#include <vector>

#include <boost/property_tree/ptree.hpp>

#include "logic/loaders/itemloader.h"
#include "logic/map/attributes/position.h"

namespace impdungeon {

struct ObjectData {
  std::string name;
  Position position;
};

class Map;

/*-------------------
* MapLoader loads maps and the content currently on the map from data files.
---------------------*/
class MapLoader {
 public:
  MapLoader(const std::string &map_file_name, 
            const std::string &item_file_name, 
            const ItemLoader &item_loader);
  virtual ~MapLoader();

  void Init();

  Map *GetMap() const;
  std::vector<ObjectData> GetItems() const;

 private:
  const std::string map_file_name_;
  const std::string item_file_name_;
  boost::property_tree::ptree root_;
  
  const ItemLoader &item_loader_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_MAP_LOADERS_MAPLOADER_H_
