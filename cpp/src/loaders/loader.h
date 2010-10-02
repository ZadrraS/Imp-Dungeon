#ifndef IMPDUNGEON_MAP_LOADERS_LOADER_H_
#define IMPDUNGEON_MAP_LOADERS_LOADER_H_

#include <boost/property_tree/ptree.hpp>

namespace impdungeon {

class Item;

class Loader {
 public:
  Loader();
  virtual ~Loader();

  virtual void Init(const std::string &file_name);

  const boost::property_tree::ptree &root() const;

 private:
  boost::property_tree::ptree root_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_MAP_LOADERS_LOADER_H_
