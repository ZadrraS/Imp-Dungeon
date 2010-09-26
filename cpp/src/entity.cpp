#include "entity.h"

namespace impdungeon {

Entity::Entity(const boost::uuids::uuid &id, 
               const std::string &name, 
               const BoundedAttribute &health)
  : id_(id),
    name_(name),
    health_(health) {
}

Entity::~Entity() {

}

void Entity::Damage(int amount) {
  health_ -= amount;
}

boost::uuids::uuid Entity::id() const {
  return id_;
}

std::string Entity::name() const {
  return name_;
}

BoundedAttribute Entity::health() const {
  return health_;
}

}  // namespace impdungeon

