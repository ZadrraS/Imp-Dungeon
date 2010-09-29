#include "world.h"

#include <fstream>
#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include "entity.h"
#include "position.h"

namespace impdungeon {

World::World() {

}

World::~World() {

}

void World::Init(const std::string &map_file_name, 
                 const std::string &entity_file_name) {
  map_.Init("../" + map_file_name);

  boost::property_tree::ptree root;
  boost::property_tree::json_parser::read_json("../" + entity_file_name, root);

  BOOST_FOREACH(boost::property_tree::ptree::value_type &value, root.get_child("")) {
    boost::property_tree::ptree health;
    health = value.second.get_child("health");

    std::cout << health.get<int>("current") << std::endl;
    Entity *entity = new Entity(
      value.first, 
      BoundedAttribute(health.get<int>("current"), health.get<int>("max")));

    Position *position = new Position(2, 2);
    entities_[entity] = position;
  
  }
}

void World::Run() {

}

void World::Destroy() {
  typedef boost::unordered_map<Entity *, Position *> map;
  BOOST_FOREACH(map::value_type entity, entities_) {
    delete entity.first;
    delete entity.second;
  }
}

}  // namespace impdungeon

