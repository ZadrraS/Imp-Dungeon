#ifndef IMPDUNGEON_LOGIC_MAP_LOADERS_ENTITYLOADER_H_
#define IMPDUNGEON_LOGIC_MAP_LOADERS_ENTITYLOADER_H_

#include <string>
#include <vector>

#include <boost/property_tree/ptree.hpp>

#include "logic/map/attributes/boundedattribute.h"
#include "logic/map/attributes/position.h"

namespace impdungeon {

class Item;
class ItemLoader;

class EntityLoader {
 public:
  EntityLoader(const std::string &file_name, 
               const ItemLoader &item_loader);
  virtual ~EntityLoader();

  void Init();

  bool IsNameRegistered(const std::string &entity_name) const;
  std::string GetPassword(const std::string &entity_name) const;
  std::string GetMap(const std::string &entity_name) const;
  Position GetPosition(const std::string &entity_name) const;    
  BoundedAttribute GetHealth(const std::string &entity_name) const;

  std::vector<Item *> GetItems(const std::string &entity_name) const;

 private:
  const std::string file_name_;
  boost::property_tree::ptree root_;

  const ItemLoader &item_loader_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_MAP_LOADERS_ENTITYLOADER_H_
