#ifndef IMPDUNGEON_LOADER_H_
#define IMPDUNGEON_LOADER_H_

#include <string>

#include <boost/property_tree/ptree.hpp>

#include "boundedattribute.h"
#include "position.h"

namespace impdungeon {

class Loader {
 public:
  Loader();
  virtual ~Loader();

  void Init(const std::string &file_name);

  std::string GetEntityPassword(const std::string &name);
  std::string GetEntityMap(const std::string &name);
  Position GetEntityPosition(const std::string &name);    
  BoundedAttribute GetEntityHealth(const std::string &name);

 private:
  boost::property_tree::ptree root_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOADER_H_
