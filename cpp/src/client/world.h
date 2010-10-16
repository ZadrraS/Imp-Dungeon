#ifndef IMPDUNGEON_CLIENT_WORLD_H_
#define IMPDUNGEON_CLIENT_WORLD_H_

#include <stdint.h>
#include <string>
#include <vector>

#include <boost/unordered_map.hpp>

#include "client/client.h"
#include "logic/map/attributes/position.h"
#include "client/inputmanager.h"

namespace impdungeon {

class Entity;
class View;

namespace client {

class World {
 public:
  World(const std::string &ip, uint16_t port);
  virtual ~World();

  void Init();
  void Run();

 private:
  void RequestUpdate();
  void Display();

  Client client_;
  InputManager input_manager_;

  View *view_;
  Entity *player_;

  boost::unordered_map<boost::uuids::uuid, Position> entities_;

  std::vector<std::string> message_log_;

  bool running_;
};

}  // namespace client
}  // namespace impdungeon

#endif  // IMPDUNGEON_CLIENT_WORLD_H_

