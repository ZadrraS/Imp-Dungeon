#include "server/server.h"

#include "logic/network/events/eventcodec.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "logic/map/attributes/position.h"
#include "logic/network/events/moveevent.h"
#include "logic/network/networkerror.h"

#include <iostream>

namespace impdungeon {

Server::Server(uint16_t port)
  : listen_socket_(-1), world_("box", "items.json", "entities.json") {
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

void Server::Run() {
  if (listen_socket_ == -1)
    throw NetworkError("Server not initialized.");

  if (listen(listen_socket_, 5) != 0)
    throw NetworkError("Error while trying to listen().");

  char buffer[EventCodec::kCodeSize];
  int client_socket;
  struct sockaddr_in client_address;
  memset(&client_address, 0, sizeof(client_address));

  socklen_t client_address_length = sizeof(struct sockaddr);
  while (true) {
    memset(&buffer, 0, sizeof(buffer));
    client_socket = accept(listen_socket_, (struct sockaddr *)&client_address, 
                           &client_address_length);
    int r_len = recv(client_socket, buffer, sizeof(buffer), 0);
    std::cout << "Client: " << inet_ntoa(client_address.sin_addr) 
              << " Received: " << r_len << " bytes." << std::endl;;

    Event *event = event_codec_.Decode(buffer);
    if (event != NULL) {
      world_.PushEvent(event);
      world_.Run(); 
    }
    close(client_socket);
  }
}

}  // namespace impdungeon

