#include "server/server.h"

#include "logic/network/events/eventcodec.h"

namespace impdungeon {

Server::Server(uint16_t port)
  : port_(port), 
    world_("box", "items.json", "entities.json") {

}

Server::~Server() {

}

void Server::Init() {
  listen_socket_ = socket(AF_INET, SOCK_STREAM, 0);
  server_address_.sin_family = AF_INET;
  server_address_.sin_addr.s_addr = htonl(INADDR_ANY); 
  server_address_.sin_port = htons(port_);
}

void Server::Run() {
  socklen_t client_address_length;
  bind(listen_socket_, (struct sockaddr *)&server_address_, 
       sizeof(server_address_));
  listen(listen_socket_, 5);
  connect_socket_ = accept(listen_socket_, (struct sockaddr*)&client_address_, 
                           &client_address_length);

  char buffer[EventCodec::kCodeSize];
  while (true) {
    recv(connect_socket_, buffer, sizeof(buffer), 0);
    world_.PushEvent(event_codec_.Decode(buffer));
    
  }
}

}  // namespace impdungeon

