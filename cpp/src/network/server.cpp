#include "server.h"

namespace impdungeon {

Server::Server(uint16_t port) : port_(port) {

}

Server::~Server() {

}

void Server::Init() {
  listen_socket_ = socket(AF_INET, SOCK_STREAM, 0);
  server_address_.sin_family = AF_INET;
  server_address_.sin_addr.s_addr = htonl(INADDR_ANY); 
  server_address_.sin_port = htons(port);
}

void Server::Listen() {
  socklen_t client_address_length;
  bind(listen_socket_, (struct sockaddr *)&server_address_, 
       sizeof(server_address_);
  listen(listen_socket_, 5);
  client_socket_ = accept(listen_socket_, (struct sockaddr*)&client_address_, 
                          &client_address_length);

  int8_t buffer[1024];
  while (true) {
    recv(client_socket_, buffer, sizeof(buffer), 0);
  }
}

}  // namespace impdungeon

