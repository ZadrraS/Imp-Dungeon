#include "client/world.h"

#include <iostream>

#include <boost/uuid/uuid.hpp>
#include <boost/foreach.hpp>

#include "logic/network/events/events.h"
#include "logic/network/message.h"

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

  Message entity_data_message(client_.Listen());
  if (!entity_data_message.ExtractSuccess()) {
    std::cout << entity_data_message.ExtractError() << std::endl;
    return;
  }
  else {
    player_ = entity_data_message.ExtractEntity();
    Position *position = entity_data_message.ExtractPosition();    
    entities_[player_->id()] = *position;
    delete position;
  }
  
  boost::uuids::uuid player_id = player_->id();
  ViewUpdateEvent view_update_event(player_id, 61, 13);
  client_.SendEvent(view_update_event);
  Message view_update_message(client_.Listen());
  view_ = view_update_message.ExtractView();
  
  while (true) {
    Display();
    ActionType action = input_manager_.GetInput();
    Position move(entities_[player_->id()]);
    switch (action) {
      case kUp: {
        move += Position(0, -1);
        break;
      }
      case kLeft: {
        move += Position(-1, 0);
        break;
      }
      case kRight: {
        move += Position(1, 0);
        break;
      }
      case kDown: {
        move += Position(0, 1);
        break;
      }
      case kLook: {

        break;
      }
      default: {

        break;
      }
    }
    MoveEvent move_event(player_id, move);
    client_.SendEvent(move_event);
    Message response(client_.Listen());
    if (response.ExtractSuccess()) {
      ViewUpdateEvent view_update_event(player_id, 61, 13);
      client_.SendEvent(view_update_event);
      Message view_update_message(client_.Listen());
      view_ = view_update_message.ExtractView();
      entities_[player_->id()] = move;
    }
    else {
      std::cout << response.ExtractError() << std::endl;
    }
    
  }
  client_.Disconnect();
}

void World::Display() {
  typedef boost::unordered_map<boost::uuids::uuid, Position> position_map;
  system("clear");
  std::cout << "/";
  for (int x = 0; x < view_->width(); x++)
    std::cout << "=";
  std::cout << "\\" << std::endl;
 
  for (int y = 0; y < view_->height(); y++) {
    std::cout << "|";
    for (int x = 0; x < view_->width(); x++) {
      char print_value = view_->GetTile(Position(x, y));
      BOOST_FOREACH(position_map::value_type it, entities_) {
        if (view_->TranslateGlobal(it.second) == Position(x, y))
          print_value = '@';
      }
      std::cout << print_value;
    }
    std::cout << "|";
    std::cout << std::endl;
  }

  std::cout << "\\";
  for (int x = 0; x < view_->width(); x++)
    std::cout << "=";
  std::cout << "/" << std::endl;
}

}  // namespace client
}  // namespace impdungeon

