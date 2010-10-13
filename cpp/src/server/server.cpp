#include "server/server.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>

#include "logic/network/networkerror.h"
#include "logic/network/events/eventhandlerinterface.h"

namespace impdungeon {
namespace server {

Server::Server(uint16_t port, EventHandlerInterface &event_handler)
  : listen_socket_(-1),
    event_handler_(event_handler) {
  memset(&server_address_, 0, sizeof(server_address_));

  server_address_.sin_family = AF_INET;
  server_address_.sin_addr.s_addr = htonl(INADDR_ANY); 
  server_address_.sin_port = htons(port);
}

Server::~Server() {

}

void Server::Init() {
  if ((listen_socket_ = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    throw NetworkError("Error creating listening socket.");
 
  if (bind(listen_socket_, (struct sockaddr *)&server_address_, 
           sizeof(server_address_)) == -1) 
    throw NetworkError("Error binding listening socket.");
}

void Server::Listen() {
  if (listen_socket_ == -1)
    throw NetworkError("Server not initialized.");

  if (listen(listen_socket_, 5) != 0)
    throw NetworkError("Error while trying to listen().");

  char buffer[Serializer::kMaxEventSize];
  int client_socket;
  struct sockaddr_in client_address;
  memset(&client_address, 0, sizeof(client_address));

  socklen_t client_address_length = sizeof(struct sockaddr);
  
  memset(&buffer, 0, sizeof(buffer));
  client_socket = accept(listen_socket_, (struct sockaddr *)&client_address, 
                         &client_address_length);
  int r_len = recv(client_socket, buffer, sizeof(buffer), 0);
  std::cout << "Client: " << inet_ntoa(client_address.sin_addr) 
            << " Received: " << r_len << " bytes." << std::endl;

  Event *event = serializer_.UnserializeEvent(buffer);
  if (event != NULL) {
    event_handler_.PushEvent(event);
  }
  
  close(client_socket);
}

}  // namespace server
}  // namespace impdungeon

