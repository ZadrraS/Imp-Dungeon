#include "logic/network/messages/itemdatamessage.h"

#include "logic/network/messages/messagevisitorinterface.h"

namespace impdungeon {

ItemDataMessage::ItemDataMessage(Item *item) : item_(item) {

}

ItemDataMessage::~ItemDataMessage() {

}

void ItemDataMessage::Acccept(MessageVisitorInterface &message_visitor) {
  message_visitor.Visit(*this);
}

}  // namespace impdungeon

