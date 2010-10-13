#include "logic/network/messages/entitydatamessage.h"

#include "logic/network/messages/messagevisitorinterface.h"

namespace impdungeon {

EntityDataMessage::EntityDataMessage(Entity *entity) 
  : Message(true), entity_(entity) {

}

EntityDataMessage::~EntityDataMessage() {

}

void EntityDataMessage::Accept(MessageVisitorInterface &message_visitor) {
  message_visitor.Visit(*this);
}

Entity *EntityDataMessage::entity() {
  return entity_;
}

}  // namespace impdungeon

