#include "logic/network/messages/itemdatamessage.h"

#include "logic/network/messages/messagevisitorinterface.h"

namespace impdungeon {

ItemDataMessage::ItemDataMessage(Entity *entity) : entity_(entity) {

}

ItemDataMessage::~ItemDataMessage() {

}

void ItemDataMessage::Acccept(MessageVisitorInterface &message_visitor) {
  message_visitor.Visit(*this);
}

}  // namespace impdungeon

