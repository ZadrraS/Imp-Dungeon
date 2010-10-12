#ifndef IMPDUNGEON_SERVER_SERVER_H_
#define IMPDUNGEON_SERVER_SERVER_H_

#include <netinet/in.h>
#include <stdint.h>

#include "logic/network/serializer.h"

namespace impdungeon {

class EventHandlerInterface;

class Server {
 public:
  Server(uint16_t port, EventHandlerInterface &event_handler);
  ~Server();

  void Init();
  void Listen();

 private:
  int listen_socket_;

  struct sockaddr_in server_address_;

  Serializer serializer_;
  EventHandlerInterface &event_handler_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_SERVER_SERVER_H_

