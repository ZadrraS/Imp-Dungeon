#include "logic/network/messages/viewupdatemessage.h"

#include "logic/map/view.h"

namespace impdungeon {

ViewUpdateMessage::ViewUpdateMessage(View *view) : view_(view) {

}

ViewUpdateMessage::~ViewUpdateMessage() {

}

void Accept(MessageVisitorInterface &message_visitor) {
  message_visitor.Visit(*this);
}

View *ViewUpdateMessage::view() {
  return view_;
}

}  // namespace impdungeon

