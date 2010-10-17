#include "client/world.h"

#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <boost/uuid/uuid.hpp>
#include <boost/foreach.hpp>

#include "logic/network/events/events.h"
#include "logic/network/message.h"

#include "logic/map/view.h"
#include "logic/map/entity.h"

namespace impdungeon {
namespace client {

World::World(const std::string &ip, uint16_t port) 
  : client_(ip, port), view_(NULL), player_(NULL), running_(false) {

}

World::~World() {
  if (view_)
    delete view_;
  if (player_)
    delete player_;
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
  std::cout << "========================END===================" << std::endl;
  RequestUpdate();

  running_ = true;
  while (running_) {
    Display();
    BOOST_FOREACH(std::string &message, message_log_) {
      std::cout << message << std::endl;
    }
    message_log_.clear();

    Position move(entities_[player_->id()]);

    ActionType action = input_manager_.GetInput();
    switch (action) {
      case kUp: {
        move += Position(0, -1);
        break;
      }
      case kDown: {
        move += Position(0, 1);
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
      case kLook: {

        break;
      }
      case kQuit: {
        running_ = false;
        continue;
        break;
      }
      default: {

        break;
      }
    }
    switch (action) {
      case kUp:
      case kDown:
      case kLeft:
      case kRight: {
        MoveEvent move_event(move);
        client_.SendEvent(move_event);
        Message response(client_.Listen());
        if (!response.ExtractSuccess()) {
          message_log_.push_back(response.ExtractError());
          continue;
        }
      }
      default:
      break;
    }

    entities_[player_->id()] = move;

    RequestUpdate();
  }
  client_.Disconnect();
}

void World::RequestUpdate() {
  ViewUpdateEvent view_update_event(61, 13);
  client_.SendEvent(view_update_event);
  Message view_update_message(client_.Listen());
  view_ = view_update_message.ExtractView();
  int entity_count = view_update_message.ExtractInt();
  for (int i = 0; i < entity_count; i++) {
    boost::uuids::uuid id = view_update_message.ExtractUuid();
    Position *position = view_update_message.ExtractPosition();
    entities_[id] = *position;
    delete position;
  }
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
        if (view_->TranslateGlobal(it.second) == Position(x, y)) {
          if (it.first == player_->id())
            print_value = '@';
          else
            print_value = 'E';
        }
      }
      std::cout << print_value;
    }
    std::cout << "|" << std::endl;
  }

  std::cout << "\\";
  for (int x = 0; x < view_->width(); x++)
    std::cout << "=";
  std::cout << "/" << std::endl;
}

}  // namespace client
}  // namespace impdungeon

