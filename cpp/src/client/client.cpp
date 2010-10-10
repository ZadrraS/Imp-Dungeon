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

Client::Client(const std::string &ip, uint16_t port) : ip_(ip), port_(port) {
  memset(&server_address_, 0, sizeof(server_address_));
}

Client::~Client() {

}

void Client::Init() {
  socket_ = socket(AF_INET, SOCK_STREAM, 0);  
  server_address_.sin_family = AF_INET;
  server_address_.sin_port = htons(port_);
    
  inet_aton(ip_.c_str(), &server_address_.sin_addr);
}

void Client::Run() {
  if (connect(socket_, (struct sockaddr*)&server_address_, 
              sizeof(server_address_)) == -1)
    throw NetworkError("Error connecting to host.");
  
  LoginEvent login_event("VartotojasVartotojauskas", "slaptasslaptazodis");
  if (send(socket_, event_codec_.Encode(login_event), EventCodec::kCodeSize, 0) == -1)
    throw NetworkError("Error sending package.");

  close(socket_);
}

}  // namespace impdungeon

