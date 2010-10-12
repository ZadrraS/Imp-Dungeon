#ifndef IMPDUNGEON_LOGIC_NETWORK_MESSAGES_ERRORMESSAGE_H_
#define IMPDUNGEON_LOGIC_NETWORK_MESSAGES_ERRORMESSAGE_H_

#include "logic/network/messages/message.h"

#include <string>

namespace impdungeon {

class ErrorMessage : public Message {
 public:
  explicit ErrorMessage(const std::string &error);
  virtual ~ErrorMessage();

  void Acccept(MessageVisitorInterface &message_visitor);

  std::string error() const;

 private:
  std::string error_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_MESSAGES_ERRORMESSAGE_H_

