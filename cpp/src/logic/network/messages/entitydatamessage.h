#ifndef IMPDUNGEON_LOGIC_NETWORK_MESSAGES_ENTITYDATAMESSAGE_H_
#define IMPDUNGEON_LOGIC_NETWORK_MESSAGES_ENTITYDATAMESSAGE_H_

#include "logic/network/messages/message.h"

namespace impdungeon {

class Entity;

class EntityDataMessage : public Message {
 public:
  EntityDataMessage(Entity *entity);
  virtual ~EntityDataMessage();

  void Accept(MessageVisitorInterface &message_visitor);

  Entity *entity();

 private:
  Entity *entity_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_MESSAGES_ENTITYDATAMESSAGE_H_

