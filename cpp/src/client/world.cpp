#include "client/world.h"

namespace impdungeon {
namespace client {

World::World(const std::string &ip, uint16_t port) : client_(ip, port) {

}

World::~World() {

}

void World::Init() {
  client_.Init();
  client_.Connect();
}

void World::Run() {
  
}

}  // namespace client
}  // namespace impdungeon

