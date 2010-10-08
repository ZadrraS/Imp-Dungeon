#include "logic/map/items/potion.h"

namespace impdungeon {

Potion::Potion(const std::string &name, int value, int strength) 
  : Item(name, value, false, true), strength_(strength) {

}

Potion::~Potion() {

}

void Potion::Equip(Entity &entity) {

}

void Potion::Use(Entity &entity) {
  entity.Heal(strength_);
}

int Potion::strength() const {
  return strength_;
}

}  // namespace impdungeon
