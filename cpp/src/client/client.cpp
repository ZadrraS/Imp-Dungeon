#include "client/client.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "logic/network/events/loginevent.h"
#include "logic/network/networkerror.h"

namespace impdungeon {

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

void Client::Run() {
  if (socket_ == -1)
    throw NetworkError("Client not initialized.");

  if (connect(socket_, (struct sockaddr*)&server_address_, 
              sizeof(server_address_)) == -1)
    throw NetworkError("Error connecting to host.");
  
  LoginEvent login_event("VartotojasVartotojauskas", "slaptasslaptazodis");
  if (send(socket_, event_codec_.Encode(login_event), EventCodec::kCodeSize, 0) == -1)
    throw NetworkError("Error sending package.");

  close(socket_);
}

}  // namespace impdungeon

