#include "map/entity.h"

#include <boost/uuid/nil_generator.hpp>

namespace impdungeon {

Entity::Entity(const std::string &name, const BoundedAttribute &health)
  : id_(boost::uuids::nil_generator()()),
    name_(name),
    health_(health) {
}

Entity::~Entity() {

}

void Entity::Damage(int amount) {
  health_ -= amount;
}

bool Entity::AssignId(const boost::uuids::uuid &id) {
  if (id_.is_nil()) {
    id_ = id;
    return true;
  }
  return false;
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

