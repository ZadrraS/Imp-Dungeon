#ifndef IMPDUNGEON_CLIENT_CLIENT_H_
#define IMPDUNGEON_CLIENT_CLIENT_H_

#include <netinet/in.h>
#include <stdint.h>

#include "logic/network/serializer.h"

namespace impdungeon {

class Event;

namespace client {

class Client {
 public:
  Client(const std::string &ip, uint16_t port);
  virtual ~Client();

  void Init();
  void Connect();
  void Disconnect();

  void SendEvent(Event &event);
  Message *Listen();

 private:
  struct sockaddr_in server_address_;
  int socket_;

  Serializer serializer_;
};

}  // namespace client
}  // namespace impdungeon

#endif  // IMPDUNGEON_CLIENT_CLIENT_H_

