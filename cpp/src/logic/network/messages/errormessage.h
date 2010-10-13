#ifndef IMPDUNGEON_LOGIC_NETWORK_MESSAGES_ERRORMESSAGE_H_
#define IMPDUNGEON_LOGIC_NETWORK_MESSAGES_ERRORMESSAGE_H_

#include "logic/network/messages/message.h"

#include <string>

namespace impdungeon {

class ErrorMessage : public Message {
 public:
  explicit ErrorMessage(const std::string &message);
  virtual ~ErrorMessage();

  void Accept(MessageVisitorInterface &message_visitor);

  std::string message() const;

 private:
  std::string message_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_MESSAGES_ERRORMESSAGE_H_

