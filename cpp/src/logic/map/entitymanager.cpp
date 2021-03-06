#include "logic/map/entitymanager.h"

#include "logic/map/entity.h"

namespace impdungeon {

EntityManager::EntityManager() {

}

EntityManager::~EntityManager() {

}

const boost::uuids::uuid EntityManager::SpawnEntity(Entity *entity) {
  if (entity->id().is_nil()) {
    entity->AssignId(uuid_generator_());
  }
  if (entities_.count(entity->id()) == 0){
    entities_[entity->id()] = entity;
  }

  return entity->id();
}

void EntityManager::DespawnEntity(const boost::uuids::uuid &id) {
  delete entities_[id];
  entities_.erase(id);
  // TODO(ZadrraS): Make this not explode in your face when handed a bad id.
}

Entity *EntityManager::GetEntity(const boost::uuids::uuid &id) {
  return entities_[id];
  // TODO(ZadrraS): Make this return NULL if a bad id is passed.
}

}  // namespace impdungeon

