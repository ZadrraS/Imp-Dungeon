#ifndef IMPDUNGEON_LOGIC_MAP_ITEMS_POTION_H_
#define IMPDUNGEON_LOGIC_MAP_ITEMS_POTION_H_

#include "logic/map/items/item.h"

namespace impdungeon {

class Potion : public Item {
 public:
  Potion(const std::string &name, int value, int strength);
  virtual ~Potion();

  void Equip(Entity &entity);
  void Use(Entity &entity);

  int strength() const;

 private:
  int strength_;

};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_MAP_ITEMS_POTION_H_
