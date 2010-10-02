#ifndef IMPDUNGEON_MAP_LOADERS_ENTITYLOADER_H_
#define IMPDUNGEON_MAP_LOADERS_ENTITYLOADER_H_

#include <string>
#include <vector>

#include "map/attributes/boundedattribute.h"
#include "map/attributes/position.h"
#include "loaders/loader.h"

namespace impdungeon {

class EntityLoader : public Loader {
 public:
  EntityLoader();
  virtual ~EntityLoader();

  std::string GetPassword(const std::string &name);
  std::string GetMap(const std::string &name);
  Position GetPosition(const std::string &name);    
  BoundedAttribute GetHealth(const std::string &name);

  std::vector<Item *> GetItems(const std::string &name);
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_MAP_LOADERS_ENTITYLOADER_H_
