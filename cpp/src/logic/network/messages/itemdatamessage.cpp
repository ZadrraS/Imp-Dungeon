#include "logic/network/messages/itemdatamessage.h"

#include "logic/network/messages/messagevisitorinterface.h"

namespace impdungeon {

ItemDataMessage::ItemDataMessage(Item *item) : Message(true), item_(item) {

}

ItemDataMessage::~ItemDataMessage() {

}

void ItemDataMessage::Accept(MessageVisitorInterface &message_visitor) {
  message_visitor.Visit(*this);
}

Item *ItemDataMessage::item() {
  return item_;
}

}  // namespace impdungeon

