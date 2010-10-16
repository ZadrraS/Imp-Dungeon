#ifndef IMPDUNGEON_SERVER_SERVER_H_
#define IMPDUNGEON_SERVER_SERVER_H_

#include <netinet/in.h>
#include <stdint.h>
#include <sys/types.h>
#include <vector>

#include <boost/uuid/uuid.hpp>
#include <boost/unordered_map.hpp>

#include "logic/network/serializer.h"
#include "server/clientmanager.h"

namespace impdungeon {

class EventHandlerInterface;
class Message;

namespace server {

class Server {
 public:
  Server(uint16_t port, EventHandlerInterface &event_handler);
  ~Server();

  void Init();
  void Disconnect();

  void SendMessage(Message &message, int descriptor);
  void Listen();

  boost::uuids::uuid GetClientId(int descriptor);
  void RegisterClient(int descriptor, boost::uuids::uuid id);
  void DisconnectClient(int descriptor);

 private:
  int listen_socket_;

  struct sockaddr_in server_address_;

  Serializer serializer_;
  EventHandlerInterface &event_handler_;
  ClientManager client_manager_;
};

}  // namespace server
}  // namespace impdungeon

#endif  // IMPDUNGEON_SERVER_SERVER_H_

