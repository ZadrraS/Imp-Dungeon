#ifndef IMPDUNGEON_LOGIC_LOADERS_ITEMLOADER_H_
#define IMPDUNGEON_LOGIC_LOADERS_ITEMLOADER_H_

#include <string>

#include <boost/property_tree/ptree.hpp>

namespace impdungeon {

class Item;

class ItemLoader {
 public:
  explicit ItemLoader(const std::string &file_name);
  virtual ~ItemLoader();

  void Init();
  
  Item *GetItem(const std::string &name) const;

 private:
  const std::string file_name_;
  boost::property_tree::ptree root_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_LOADERS_ITEMLOADER_H_
