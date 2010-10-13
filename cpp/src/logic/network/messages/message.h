#ifndef IMPDUNGEON_LOGIC_NETWORK_MESSAGES_MESSAGE_H_
#define IMPDUNGEON_LOGIC_NETWORK_MESSAGES_MESSAGE_H_

namespace impdungeon {

class MessageVisitorInterface;

class Message {
 public:
  Message(bool success);
  virtual ~Message();

  virtual void Accept(MessageVisitorInterface &message_visitor) = 0;

  bool success() const;

 private:
  bool success_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_MESSAGES_MESSAGE_H_

