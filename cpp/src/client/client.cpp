#include "client/client.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "logic/network/events/event.h"
#include "logic/network/networkerror.h"

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

Message *Client::Listen() {
  char buffer[Serializer::kMaxMessageSize];
  if (recv(socket_, buffer, sizeof(buffer), 0) == -1)
    throw NetworkError("Error receiving package.");
  Message *message = serializer_.UnserializeMessage(buffer);
  return message;
}

}  // namespace client
}  // namespace impdungeon

