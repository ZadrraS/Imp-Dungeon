#include "client/world.h"

#include <iostream>

#include <boost/uuid/uuid.hpp>

#include "logic/network/events/events.h"
#include "logic/network/messages/messages.h"

#include "logic/map/view.h"
#include "logic/map/entity.h"

namespace impdungeon {
namespace client {

World::World(const std::string &ip, uint16_t port) 
  : client_(ip, port), view_(NULL), player_(NULL) {

}

World::~World() {
  if (view_)
    delete view_;
  if (player_)
    delete player_;
  
  client_.Disconnect();
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

  Message *message = NULL;
  message = client_.Listen();
  message->Accept(*this);
  delete message;
  
  boost::uuids::uuid id = player_->id();
  ViewUpdateEvent view_update_event(id, 61, 17);
  client_.SendEvent(view_update_event);
  message = client_.Listen();
  message->Accept(*this);
  delete message;

  Display();
  client_.Disconnect();
}

void World::Visit(ErrorMessage &error_message) {
  std::cout << error_message.message() << std::endl;
}

void World::Visit(EntityDataMessage &entity_data_message) {
  if (player_ == NULL)
    player_ = entity_data_message.entity();
}

void World::Visit(ItemDataMessage &item_data_message) {

}

void World::Visit(ViewUpdateMessage &view_update_message) {
  if (view_ == NULL)
    view_ = view_update_message.view();
}

void World::Display() {
  for (int y = 0; y < view_->height(); y++) {
    for (int x = 0; x < view_->width(); x++) {
      std::cout << view_->GetTile(Position(x, y));
    }
    std::cout << std::endl;
  }
}

}  // namespace client
}  // namespace impdungeon

