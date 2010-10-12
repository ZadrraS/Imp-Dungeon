#include "logic/network/messages/errormessage.h"

#include "logic/network/messages/messagevisitorinterface.h"

namespace impdungeon {

ErrorMessage::ErrorMessage(const std::string &error) : error_(error) {

}

ErrorMessage::~ErrorMessage() {

}

void ErrorMessage::Accept(MessageVisitorInterface &message_visitor) {
  message_visitor.Visit(*this);
}

std::string ErrorMessage::error() const {
  return error_;
}

}  // namespace impdungeon

