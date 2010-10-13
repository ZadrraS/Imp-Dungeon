#include "logic/network/messages/errormessage.h"

#include "logic/network/messages/messagevisitorinterface.h"

namespace impdungeon {

ErrorMessage::ErrorMessage(const std::string &message) 
  : Message(false),
    message_(message) {

}

ErrorMessage::~ErrorMessage() {

}

void ErrorMessage::Accept(MessageVisitorInterface &message_visitor) {
  message_visitor.Visit(*this);
}

std::string ErrorMessage::message() const {
  return message_;
}

}  // namespace impdungeon

