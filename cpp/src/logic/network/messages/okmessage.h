#ifndef IMPDUNGEON_LOGIC_NETWORK_MESSAGES_OKMESSAGE_H_
#define IMPDUNGEON_LOGIC_NETWORK_MESSAGES_OKMESSAGE_H_

#include "logic/network/messages/message.h"

namespace impdungeon {

class OkMessage : public Message {
 public:
  OkMessage();
  virtual ~OkMessage();

  void Accept(MessageVisitorInterface &message_visitor);
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_MESSAGES_OKMESSAGE_H_

