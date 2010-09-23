#include "Entity.h"

namespace impdungeon {

Entity::Entity(boost::uuids::uuid id, std::string &name, BoundedAttribute &health)
  : id_(id),
    name_(name),
    health_(health) {
}

Entity::~Entity() {

}

void Entity::Damage(int amount) {
  health -= amount;
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

