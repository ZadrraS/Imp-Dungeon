#ifndef IMPDUNGEON_MAP_LOADERS_ENTITYLOADER_H_
#define IMPDUNGEON_MAP_LOADERS_ENTITYLOADER_H_

#include <string>
#include <vector>

#include "map/attributes/boundedattribute.h"
#include "map/attributes/position.h"
#include "loaders/loader.h"

namespace impdungeon {

class Item;
class Map;

struct PositionedItem {
  Item *item;
  Position position;
};

class EntityLoader : public Loader {
 public:
  EntityLoader();
  virtual ~EntityLoader();

  void Init(const std::string &file_name, 
            const std::string &item_file_name,
            const std::string &map_name);

  std::string GetEntityPassword(const std::string &name);
  std::string GetEntityMap(const std::string &name);
  Position GetEntityPosition(const std::string &name);    
  BoundedAttribute GetEntityHealth(const std::string &name);

  std::vector<Item *> GetEntityItems(const std::string &name);

  Map *GetMap();
  std::vector<PositionedItem> GetItems();

 private:
  Item *ConstructItem(const std::string &name);

  boost::property_tree::ptree item_database_;
  boost::property_tree::ptree map_root_;
  std::string map_name_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_MAP_LOADERS_ENTITYLOADER_H_
