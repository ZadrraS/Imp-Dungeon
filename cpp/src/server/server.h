#ifndef IMPDUNGEON_SERVER_SERVER_H_
#define IMPDUNGEON_SERVER_SERVER_H_

#include <netinet/in.h>
#include <stdint.h>
#include <sys/types.h>
#include <vector>

#include <boost/uuid/uuid.hpp>
#include <boost/unordered_map.hpp>

#include "logic/network/serializer.h"

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
  void AddClientId(int descriptor, boost::uuids::uuid id);
  void RemoveClientId(int descriptor);

 private:
  void DisconnectClient(int descriptor);

  int listen_socket_;

  struct sockaddr_in server_address_;

  Serializer serializer_;
  EventHandlerInterface &event_handler_;

  boost::unordered_map<int, boost::uuids::uuid> client_ids_; 
  std::vector<int> descriptor_list_;
  fd_set descriptors_;
  int max_descriptor_;
};

}  // namespace server
}  // namespace impdungeon

#endif  // IMPDUNGEON_SERVER_SERVER_H_

