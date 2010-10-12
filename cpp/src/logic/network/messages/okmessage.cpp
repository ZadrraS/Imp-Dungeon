#include "logic/network/messages/okmessage.h"

#include "logic/network/messages/messagevisitorinterface.h"

namespace impdungeon {

OkMessage::OkMessage() {

}

OkMessage::~OkMessage() {

}

void OkMessage::Accept(MessageVisitorInterface &message_visitor) {
  message_visitor.Visit(*this);
}

}  // namespace impdungeon

