#include "client/client.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "logic/network/events/event.h"
#include "logic/network/message.h"
#include "logic/network/networkerror.h"
#include <iostream>

namespace impdungeon {
namespace client {

Client::Client(const std::string &ip, uint16_t port) : socket_(-1) {
  memset(&server_address_, 0, sizeof(server_address_));
  
  server_address_.sin_family = AF_INET;
  server_address_.sin_port = htons(port);
    
  if (inet_aton(ip.c_str(), &server_address_.sin_addr) == 0)
    throw NetworkError("Invalid remote IP address.");
}

Client::~Client() {
  
}

void Client::Init() {
  socket_ = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_ == -1)
    throw NetworkError("Error creating socket.");
}

void Client::Connect() {
  if (socket_ == -1)
    throw NetworkError("Client not initialized.");

  if (connect(socket_, (struct sockaddr*)&server_address_, 
              sizeof(server_address_)) == -1)
    throw NetworkError("Error connecting to host.");
}

void Client::Disconnect() {
  close(socket_);
}

void Client::SendEvent(Event &event) {
  char *data = serializer_.SerializeEvent(event);
  if (send(socket_, data, Serializer::kMaxEventSize, 0) == -1)
    throw NetworkError("Error sending package.");
  delete [] data;
}

char *Client::Listen() {
  char *buffer = new char[Message::kMaxBufferSize];
  if (recv(socket_, buffer, Message::kMaxBufferSize, 0) <= 0)
    throw NetworkError("Error receiving package.");  
  return buffer;
}

}  // namespace client
}  // namespace impdungeon

