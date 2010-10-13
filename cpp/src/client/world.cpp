#include "client/world.h"

#include <iostream>

#include "logic/network/events/loginevent.h"
#include "logic/network/messages/errormessage.h"
#include "logic/network/messages/entitydatamessage.h"
#include "logic/network/messages/itemdatamessage.h"
#include "logic/network/messages/viewupdatemessage.h"

namespace impdungeon {
namespace client {

World::World(const std::string &ip, uint16_t port) : client_(ip, port) {

}

World::~World() {

}

void World::Init() {
  client_.Init();
  client_.Connect();
}

void World::Run() {
  std::string user_name;
  std::cout << "Enter your user name: ";
  std::cin >> user_name;
  LoginEvent login_event(user_name, "dummypassword");
  client_.SendEvent(login_event);

  Message *message = client_.Listen();
  message->Accept(*this);
  delete message;
}

void World::Visit(ErrorMessage &error_message) {
  std::cout << error_message.message() << std::endl;
}

void World::Visit(EntityDataMessage &entity_data_message) {

}

void World::Visit(ItemDataMessage &item_data_message) {

}

void World::Visit(ViewUpdateMessage &view_update_message) {

}

}  // namespace client
}  // namespace impdungeon

