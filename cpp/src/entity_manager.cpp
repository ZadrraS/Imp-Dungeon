#include "EntityManager.h"

#include <boost/uuid/uuid_generators.hpp>

namespace impdungeon {

EntityFactory::EntityFactory() {

}

EntityFactory::~EntityFactory() {

}

boost::uuids::uuid &EntityFactory::GenerateEntity(
    std::string &name,
    BoundedAttribute &health) {
  Entity *new_entity = new Entity(boost::uuids::random_generator(), name, health);
  entities_[new_entity->id()] = new_entity;

  return new_entity->id();
}

void EntityFactory::DestroyEntity(boost::uuids::uuid &id) {
  entities_.erase(id);
  //  TODO(ZadrraS): Make this not explode in your face when handed a bad id.
}

Entity *EntityFactory::entity(boost::uuids::uuid &id) const {
  return entities_[id];
  //  TODO(ZadrraS): Make this return NULL if a bad id is passed.
}

}  // namespace impdungeon

