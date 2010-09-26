#include "world.h"

namespace impdungeon {

World::World() {

}

World::~World() {

}

void World::Init() {
  map_.Init("../map.txt");
}

void World::Run() {

}

}  // namespace impdungeon

