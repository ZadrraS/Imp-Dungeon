#include "server/server.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>

#include "logic/network/networkerror.h"
#include "logic/network/events/eventhandlerinterface.h"
#include "logic/network/messages/message.h"
#include <iostream>

namespace impdungeon {
namespace server {

Server::Server(uint16_t port, EventHandlerInterface &event_handler)
  : listen_socket_(-1),
    event_handler_(event_handler) {
  memset(&server_address_, 0, sizeof(server_address_));
  memset(&client_address_, 0, sizeof(client_address_));

  server_address_.sin_family = AF_INET;
  server_address_.sin_addr.s_addr = htonl(INADDR_ANY); 
  server_address_.sin_port = htons(port);
}

Server::~Server() {
  Disconnect();
  close(listen_socket_);
}

void Server::Init() {
  if ((listen_socket_ = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    throw NetworkError("Error creating listening socket.");
 
  if (bind(listen_socket_, (struct sockaddr *)&server_address_, 
           sizeof(server_address_)) == -1) 
    throw NetworkError("Error binding listening socket.");

  if (listen(listen_socket_, 5) != 0)
    throw NetworkError("Error while trying to listen().");

  socklen_t client_address_length = sizeof(struct sockaddr);
  client_socket_ = accept(listen_socket_, (struct sockaddr *)&client_address_, 
                         &client_address_length);
}

void Server::Disconnect() {
  close(client_socket_);
}

void Server::SendMessage(Message &message) {  
  char *data = serializer_.SerializeMessage(message);
  int s_len = send(client_socket_, data, Serializer::kMaxMessageSize, 0);
  if (s_len <= 0)
    throw NetworkError("Error sending package.");

  std::cout << "Client: " << inet_ntoa(client_address_.sin_addr) 
            << " Sent: " << s_len << " bytes." << std::endl;
  delete [] data;
}

void Server::Listen() {
  if (listen_socket_ == -1)
    throw NetworkError("Server not initialized.");
 
  if (listen(listen_socket_, 5) != 0)
    throw NetworkError("Error while trying to listen().");

  char buffer[Serializer::kMaxEventSize];
  memset(&buffer, 0, sizeof(buffer));
  
  int r_len = recv(client_socket_, buffer, sizeof(buffer), 0);
  if (r_len <= 0)
    throw NetworkError("Error receiving package.");
  std::cout << "Client: " << inet_ntoa(client_address_.sin_addr) 
            << " Received: " << r_len << " bytes." << std::endl;

  Event *event = serializer_.UnserializeEvent(buffer);
  if (event != NULL) {
    event_handler_.PushEvent(event);
  }
}

}  // namespace server
}  // namespace impdungeon

