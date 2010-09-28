#include "entitymanager.h"

#include "entity.h"

namespace impdungeon {

EntityManager::EntityManager() {

}

EntityManager::~EntityManager() {

}

const boost::uuids::uuid EntityManager::GenerateEntity(
    const std::string &name,
    const BoundedAttribute &health) {
  Entity *new_entity = new Entity(uuid_generator_(), name, health);
  entities_[new_entity->id()] = new_entity;

  return new_entity->id();
}

void EntityManager::DestroyEntity(const boost::uuids::uuid &id) {
  entities_.erase(id);
  //  TODO(ZadrraS): Make this not explode in your face when handed a bad id.
}

Entity *EntityManager::entity(const boost::uuids::uuid &id) {
  return entities_[id];
  //  TODO(ZadrraS): Make this return NULL if a bad id is passed.
}

}  // namespace impdungeon

