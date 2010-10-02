#ifndef IMPDUNGEON_LOADER_H_
#define IMPDUNGEON_LOADER_H_

#include <string>
#include <vector>

#include <boost/property_tree/ptree.hpp>

#include "map/attributes/boundedattribute.h"
#include "map/attributes/position.h"

namespace impdungeon {

class Item;

class Loader {
 public:
  Loader();
  virtual ~Loader();

  void Init(const std::string &file_name);

  std::string GetEntityPassword(const std::string &name);
  std::string GetEntityMap(const std::string &name);
  Position GetEntityPosition(const std::string &name);    
  BoundedAttribute GetEntityHealth(const std::string &name);

  std::vector<Item *> GetEntityItems(const std::string &name);

 private:
  boost::property_tree::ptree root_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOADER_H_
