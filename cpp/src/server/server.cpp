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
}

Server::~Server() {
  DisconnectAll();
}

void Server::Init() {
  if ((listen_socket_ = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    throw NetworkError("Error creating listening socket.");

  if (bind(listen_socket_, (struct sockaddr *)&server_address_, 
           sizeof(server_address_)) == -1) 
    throw NetworkError("Error binding listening socket.");

  client_manager_.AddClient(listen_socket_);
}

void Server::Listen() {
  if (listen_socket_ == -1)
    throw NetworkError("Server not initialized.");

  if (listen(listen_socket_, 10) == -1)
    throw NetworkError("Error listen()'ing.");

  fd_set read_descriptors;
  FD_ZERO(&read_descriptors);
  read_descriptors = client_manager_.CopyClientDescriptors();

  if (select(client_manager_.max_descriptor() + 1, &read_descriptors, 
             NULL, NULL, NULL) == -1) 
    throw NetworkError("Error select()'ing.");

  BOOST_FOREACH(int descriptor, client_manager_) {
    if (FD_ISSET(descriptor, &read_descriptors)) {
      if (descriptor == listen_socket_) {  // New client connecting
        socklen_t client_address_length = sizeof(struct sockaddr);
        struct sockaddr_in client_address;
        memset(&client_address, 0, sizeof(client_address));

        int new_descriptor = accept(listen_socket_,
                                    (struct sockaddr *)&client_address,
                                    &client_address_length);
        if (new_descriptor != -1) {
          client_manager_.AddClient(new_descriptor);

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
          std::cout << "Client " << descriptor 
                    << " has disconnected." << std::endl;
          if (client_manager_.IsClientRegistered(descriptor)) {
            Event *kick_event = new LogoffEvent();
            kick_event->set_descriptor(descriptor);
            event_handler_.PushEvent(kick_event);
          }
          else {
            DisconnectClient(descriptor);
          }
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

            if (client_manager_.IsClientRegistered(descriptor)) {
              Event *kick_event = new LogoffEvent();
              kick_event->set_descriptor(descriptor);
              event_handler_.PushEvent(kick_event);
            }
            else {
              DisconnectClient(descriptor);
            }
          }
        }
      }
    }
  }
}

boost::uuids::uuid Server::GetClientId(int descriptor) {
  return client_manager_.GetClientId(descriptor);
}

void Server::RegisterClient(int descriptor, boost::uuids::uuid id) {
  client_manager_.RegisterClient(descriptor, id);
}

void Server::DisconnectClient(int descriptor) {
  client_manager_.RemoveClient(descriptor);
  close(descriptor);
}

void Server::DisconnectAll() {
  BOOST_FOREACH(int descriptor, client_manager_) {
    DisconnectClient(descriptor);
  }
}

void Server::PushMessage(Message *message, int descriptor) {
  messages_.push(message_socket_t(message, descriptor));
}

void Server::DispatchMessages() {
  while (!messages_.empty()) {
    message_socket_t message_socket = messages_.front();
    SendMessage(message_socket.first, message_socket.second);
    delete message_socket.first;
    messages_.pop();
  }
}

void Server::SendMessage(Message *message, int descriptor) {
  if (client_manager_.HasClient(descriptor)) {
    int s_len = send(descriptor, message->buffer(), Message::kMaxBufferSize, 0);
    if (s_len <= 0) {
      std::cout << "Client " << descriptor
                << " is not listening. Kicking from server..." << std::endl;

      if (client_manager_.IsClientRegistered(descriptor)) {
        Event *kick_event = new LogoffEvent();
        kick_event->set_descriptor(descriptor);
        event_handler_.PushEvent(kick_event);
      }
      else {
        DisconnectClient(descriptor);
      }
    }
  }
}

}  // namespace server
}  // namespace impdungeon

