#ifndef IMPDUNGEON_LOGIC_NETWORK_MESSAGES_ITEMDATAMESSAGE_H_
#define IMPDUNGEON_LOGIC_NETWORK_MESSAGES_ITEMDATAMESSAGE_H_

#include "logic/network/messages/message.h"

namespace impdungeon {

class Item;

class ItemDataMessage : public Message {
 public:
  ItemDataMessage(Item *item);
  virtual ~ItemDataMessage();

  void Acccept(MessageVisitorInterface &message_visitor);

 private:
  Item *item_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_MESSAGES_ITEMDATAMESSAGE_H_

