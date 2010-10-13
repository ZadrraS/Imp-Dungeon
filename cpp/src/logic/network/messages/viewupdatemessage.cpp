#include "logic/network/messages/viewupdatemessage.h"

#include "logic/map/view.h"

namespace impdungeon {

ViewUpdateMessage::ViewUpdateMessage(View *view) : Message(true), view_(view) {

}

ViewUpdateMessage::~ViewUpdateMessage() {

}

void ViewUpdateMessage::Accept(MessageVisitorInterface &message_visitor) {
  message_visitor.Visit(*this);
}

View *ViewUpdateMessage::view() {
  return view_;
}

}  // namespace impdungeon

