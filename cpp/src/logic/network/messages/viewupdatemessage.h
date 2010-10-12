#ifndef IMPDUNGEON_LOGIC_NETWORK_MESSAGES_VIEWUPDATEMESSAGE_H_
#define IMPDUNGEON_LOGIC_NETWORK_MESSAGES_VIEWUPDATEMESSAGE_H_

#include "logic/network/messages/message.h"

#include "logic/network/messages/messagevisitorinterface.h"

namespace impdungeon {

class MessageVisitorInterface;

class View;

class ViewUpdateMessage : public Message {
 public:
  ViewUpdateMessage(View *view);
  virtual ~ViewUpdateMessage();

  void Accept(MessageVisitorInterface &message_visitor);

  View *view();

 private:
  View *view_;  
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_MESSAGES_VIEWUPDATEMESSAGE_H_

