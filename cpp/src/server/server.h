#ifndef IMPDUNGEON_SERVER_SERVER_H_
#define IMPDUNGEON_SERVER_SERVER_H_

#include <netinet/in.h>
#include <stdint.h>
#include <sys/types.h>
#include <vector>
#include <queue>

#include <boost/uuid/uuid.hpp>
#include <boost/unordered_map.hpp>

#include "logic/network/serializer.h"
#include "server/clientmanager.h"
#include "logic/network/message.h"

namespace impdungeon {

class EventHandlerInterface;

namespace server {

class Server {
 public:
  Server(uint16_t port, EventHandlerInterface &event_handler);
  ~Server();

  void Init();

  void Listen();

  boost::uuids::uuid GetClientId(int descriptor);
  void RegisterClient(int descriptor, boost::uuids::uuid id);
  void DisconnectClient(int descriptor);
  void DisconnectAll();

  void PushMessage(Message *message, int descriptor);
  void DispatchMessages();  

 private:
  void SendMessage(Message *message, int descriptor);

  int listen_socket_;

  struct sockaddr_in server_address_;

  Serializer serializer_;
  EventHandlerInterface &event_handler_;
  ClientManager client_manager_;

  typedef std::pair<Message *, int> message_socket_t;
  std::queue<message_socket_t> messages_;
};

}  // namespace server
}  // namespace impdungeon

#endif  // IMPDUNGEON_SERVER_SERVER_H_

