#include "logic/network/messages/message.h"

namespace impdungeon {

Message::Message(bool success) : success_(success) {

}

Message::~Message() {

}

bool Message::success() const {
  return success_;
}

}  // namespace impdungeon

