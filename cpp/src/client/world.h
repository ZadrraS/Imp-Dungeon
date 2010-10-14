#ifndef IMPDUNGEON_CLIENT_WORLD_H_
#define IMPDUNGEON_CLIENT_WORLD_H_

#include <stdint.h>
#include <string>

#include "client/client.h"
#include "logic/network/messages/messagevisitorinterface.h"

namespace impdungeon {

class Entity;
class View;

namespace client {

class World : public MessageVisitorInterface {
 public:
  World(const std::string &ip, uint16_t port);
  virtual ~World();

  void Init();
  void Run();

 private:
  // Inherited from MessageVisitorInterface
  void Visit(ErrorMessage &error_message);
  void Visit(EntityDataMessage &entity_data_message);
  void Visit(ItemDataMessage &item_data_message);
  void Visit(ViewUpdateMessage &view_update_message);

  void Display();

  Client client_;

  View *view_;
  Entity *player_;  
};

}  // namespace client
}  // namespace impdungeon

#endif  // IMPDUNGEON_CLIENT_WORLD_H_

