#ifndef IMPDUNGEON_MAP_LOADERS_MAPLOADER_H_
#define IMPDUNGEON_MAP_LOADERS_MAPLOADER_H_

#include <vector>

#include "loaders/loader.h"
#include "map/attributes/position.h"

namespace impdungeon {

struct PositionedItem {
  Item *item;
  Position position;
};

class Map;

/*-------------------
* MapLoader loads maps and the content currently on the map from data files.
---------------------*/
class MapLoader : public Loader {
 public:
  MapLoader();
  virtual ~MapLoader();

  void Init(const std::string &map_name);

  Map *GetMap();
  std::vector<PositionedItem> GetItems();

 private:
  std::string map_name_;
  
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_MAP_LOADERS_MAPLOADER_H_
