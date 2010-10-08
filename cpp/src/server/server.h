#ifndef IMPDUNGEON_SERVER_SERVER_H_
#define IMPDUNGEON_SERVER_SERVER_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdint.h>

namespace impdungeon {

class Server {
 public:
  Server(uint16_t port);
  ~Server();

  void Init();
  void Listen();

 private:
  uint16_t port_;
  int listen_socket_;
  int connect_socket_;

  struct sockaddr_in server_address_;
  struct sockaddr_in client_address_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_SERVER_SERVER_H_

