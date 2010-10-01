#include "loader.h"

#include <boost/property_tree/json_parser.hpp>

#include "boundedattribute.h"
#include "entity.h"

namespace impdungeon {

Loader::Loader() {
  
}

Loader::~Loader() {

}

void Loader::Init(const std::string &file_name) {
  boost::property_tree::json_parser::read_json(file_name, root_);
}

std::string Loader::GetEntityPassword(const std::string &name) {
  return root_.get<std::string>(name + ".password");
}

std::string Loader::GetEntityMap(const std::string &name) {
  return root_.get<std::string>(name + ".map");
}

Position Loader::GetEntityPosition(const std::string &name) {
  int x, y;
  x = root_.get<int>(name + ".position.x");
  y = root_.get<int>(name + ".position.y");

  return Position(x, y);
}  

BoundedAttribute Loader::GetEntityHealth(const std::string &name) {
  int current, max;
  current = root_.get<int>(name + ".health.current");
  max = root_.get<int>(name + ".health.max");

  return BoundedAttribute(current, max);
}

}  // namespace impdungeon

