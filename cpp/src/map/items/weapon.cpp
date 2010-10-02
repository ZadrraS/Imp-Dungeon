#include "map/items/weapon.h"

namespace impdungeon {
Weapon::Weapon(const std::string &name, int value, 
               int min_damage, int max_damage)
  : Item(name, value, true, false), 
    min_damage_(min_damage), max_damage_(max_damage) {

}

Weapon::~Weapon() {

}

void Weapon::Equip(Entity &entity) {
  entity.EquipWeapon(this);
}

void Weapon::Use(Entity &entity) {
  
}

int Weapon::min_damage() const {
  return min_damage_;
}

int Weapon::max_damage() const {
  return max_damage_;
}

}  // namespace impdungeon
