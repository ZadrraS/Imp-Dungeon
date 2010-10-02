#ifndef IMPDUNGEON_WEAPON_H_
#define IMPDUNGEON_WEAPON_H_

#include "map/items/item.h"

namespace impdungeon {

class Weapon : public Item {
 public:
  Weapon(const std::string &name, int value, int min_damage, int max_damage);
  virtual ~Weapon();

  void Equip(Entity &entity);
  void Use(Entity &entity);

  int min_damage() const;
  int max_damage() const;

 private:
  int min_damage_;
  int max_damage_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_WEAPON_H_
