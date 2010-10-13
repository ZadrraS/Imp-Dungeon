#ifndef IMPDUNGEON_CLIENT_WORLD_H_
#define IMPDUNGEON_CLIENT_WORLD_H_

#include <stdint.h>
#include <string>

#include "client/client.h"

namespace impdungeon {
namespace client {

class World {
 public:
  World(const std::string &ip, uint16_t port);
  virtual ~World();

  void Init();
  void Run();

 private:
  Client client_;
  
};

}  // namespace client
}  // namespace impdungeon

#endif  // IMPDUNGEON_CLIENT_WORLD_H_

