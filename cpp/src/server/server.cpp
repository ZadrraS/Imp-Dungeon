#include "server/server.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <iostream>
#include <algorithm>
#include <cstring>

#include <boost/foreach.hpp>

#include "logic/network/networkerror.h"
#include "logic/network/events/eventhandlerinterface.h"
#include "logic/network/events/event.h"
#include "logic/network/events/logoffevent.h"
#include "logic/network/message.h"

namespace impdungeon {
namespace server {

Server::Server(uint16_t port, EventHandlerInterface &event_handler)
  : listen_socket_(-1),
    event_handler_(event_handler) {
  memset(&server_address_, 0, sizeof(server_address_));

  server_address_.sin_family = AF_INET;
  server_address_.sin_addr.s_addr = htonl(INADDR_ANY); 
  server_address_.sin_port = htons(port);

  FD_ZERO(&descriptors_);
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

  FD_SET(listen_socket_, &descriptors_);
  max_descriptor_ = listen_socket_;
  descriptor_list_.push_back(listen_socket_);
}

void Server::Disconnect() {
}

void Server::SendMessage(Message &message, int descriptor) {
  if (std::find(descriptor_list_.begin(), descriptor_list_.end(), descriptor) !=
      descriptor_list_.end()) {
    int s_len = send(descriptor, message.buffer(), Message::kMaxBufferSize, 0);
    if (s_len <= 0) {
      std::cout << "Client " << descriptor
                << " is not listening. Kicking from server..." << std::endl;
      DisconnectClient(descriptor);
    }
  }
}

void Server::Listen() {
  if (listen_socket_ == -1)
    throw NetworkError("Server not initialized.");

  if (listen(listen_socket_, 10) == -1)
    throw NetworkError("Error listen()'ing.");

  fd_set read_descriptors;
  FD_ZERO(&read_descriptors);
  read_descriptors = descriptors_;

  if (select(max_descriptor_ + 1, &read_descriptors, NULL, NULL, NULL) == -1) 
    throw NetworkError("Error select()'ing.");

  std::vector<int> disconnection_list;

  

  BOOST_FOREACH(int &descriptor, descriptor_list_) {
    if (FD_ISSET(descriptor, &read_descriptors)) {
      if (descriptor == listen_socket_) {  // New client connecting
        socklen_t client_address_length = sizeof(struct sockaddr);
        struct sockaddr_in client_address;
        memset(&client_address, 0, sizeof(client_address));

        int new_descriptor = accept(listen_socket_,
                                    (struct sockaddr *)&client_address,
                                    &client_address_length);
        if (new_descriptor != -1) {
          FD_SET(new_descriptor, &descriptors_);
          descriptor_list_.push_back(new_descriptor);

          if (new_descriptor > max_descriptor_)
            max_descriptor_ = new_descriptor;

          std::cout << "New connection from "
                    << inet_ntoa(client_address.sin_addr) 
                    << ". Assigning descriptor: " << new_descriptor << "." 
                    << std::endl;
        }
      }
      else {  // Client sending data
        char buffer[Serializer::kMaxEventSize];
        memset(&buffer, 0, sizeof(buffer));
        int r_len = recv(descriptor, buffer, sizeof(buffer), 0);
        if (r_len <= 0) {  // Lost connection to client
          std::cout << "Client " << descriptor << " has disconnected." << std::endl;
          disconnection_list.push_back(descriptor);
        }
        else {  // Parse clients sent data
          Event *event = serializer_.UnserializeEvent(buffer);
          if (event != NULL) {
            event->set_descriptor(descriptor);
            event_handler_.PushEvent(event);
          }
          else {
            std::cout << "Client " << descriptor << " is sending malformed data. "
                      << "Kicking from server..." << std::endl;
            disconnection_list.push_back(descriptor);
          }
        }
      }
    }
  }

  BOOST_FOREACH(int &descriptor, disconnection_list) {
    DisconnectClient(descriptor);
  }
}

boost::uuids::uuid Server::GetClientId(int descriptor) {
  // TODO(ZadrraS): Make this not explode when handed a bad descriptor.
  return client_ids_[descriptor];
}

void Server::AddClientId(int descriptor, boost::uuids::uuid id) {
  if (std::find(descriptor_list_.begin(), descriptor_list_.end(), descriptor) !=
      descriptor_list_.end()) {
    client_ids_[descriptor] = id;
  }
}

void Server::RemoveClientId(int descriptor) {
  client_ids_.erase(descriptor);
}

void Server::DisconnectClient(int descriptor) {
  FD_CLR(descriptor, &descriptors_);
  descriptor_list_.erase(std::remove(descriptor_list_.begin(),
                                     descriptor_list_.end(),
                                     descriptor), descriptor_list_.end());
  close(descriptor);

  if (client_ids_.count(descriptor) > 0) {
    Event *event = new LogoffEvent();
    event->set_descriptor(descriptor);
    event_handler_.PushEvent(event);
  }
}

}  // namespace server
}  // namespace impdungeon

