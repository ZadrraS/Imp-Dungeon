#ifndef IMPDUNGEON_CLIENT_CLIENT_H_
#define IMPDUNGEON_CLIENT_CLIENT_H_

#include <netinet/in.h>
#include <stdint.h>

#include "logic/network/events/eventcodec.h"

namespace impdungeon {

class Client {
 public:
  Client(const std::string &ip, uint16_t port);
  virtual ~Client();

  void Init();
  void Run();

 private:
  std::string ip_;
  uint16_t port_;
  int socket_;

  struct sockaddr_in server_address_;
  EventCodec event_codec_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_CLIENT_CLIENT_H_

