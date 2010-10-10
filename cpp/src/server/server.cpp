#include "server/server.h"

#include "logic/network/events/eventcodec.h"

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
  : port_(port), 
    world_("box", "items.json", "entities.json") {
  memset(&server_address_, 0, sizeof(server_address_));
  memset(&client_address_, 0, sizeof(client_address_));

  server_address_.sin_family = AF_INET;
  server_address_.sin_addr.s_addr = htonl(INADDR_ANY); 
  server_address_.sin_port = htons(port_);
}

Server::~Server() {

}

void Server::Init() {
  if ((listen_socket_ = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    throw NetworkError("Error creating listening socket.");
 
  if (bind(listen_socket_, (struct sockaddr *)&server_address_, 
           sizeof(server_address_)) < 0) 
    throw NetworkError("Error binding listening socket.");
}

void Server::Run() {
  socklen_t client_address_length = sizeof(struct sockaddr);
  if (listen(listen_socket_, 5) != 0)
    throw NetworkError("Error while trying to listen().");

  char buffer[EventCodec::kCodeSize];
  while (true) {
    memset(&buffer, 0, sizeof(buffer));
    connect_socket_ = accept(listen_socket_, (struct sockaddr *)&client_address_, 
                             &client_address_length);
    int r_len = recv(connect_socket_, buffer, sizeof(buffer), 0);
    std::cout << "Client: " << inet_ntoa(client_address_.sin_addr) 
              << " Received: " << r_len << " bytes." << std::endl;;

    Event *event = event_codec_.Decode(buffer);
    if (event != NULL) {
      world_.PushEvent(event);
      world_.Run(); 
    }
    close(connect_socket_);
  }
}

}  // namespace impdungeon

