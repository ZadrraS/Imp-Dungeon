#ifndef IMPDUNGEON_LOGIC_NETWORK_MESSAGES_VIEWUPDATEMESSAGE_H_
#define IMPDUNGEON_LOGIC_NETWORK_MESSAGES_VIEWUPDATEMESSAGE_H_

namespace impdungeon {

class MessageVisitorInterface;

class ViewUpdateMessage {
 public:
  ViewUpdateMessage(char *view);
  virtual ~ViewUpdateMessage();

  virtual void Accept(MessageVisitorInterface &message_visitor) = 0;

 private:
  char *view_;  
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_MESSAGES_VIEWUPDATEMESSAGE_H_

