#include "loaders/loader.h"

#include <boost/property_tree/json_parser.hpp>

namespace impdungeon {

Loader::Loader() {
  
}

Loader::~Loader() {

}

void Loader::Init(const std::string &file_name) {
  boost::property_tree::json_parser::read_json(file_name, root_);
}

const boost::property_tree::ptree &Loader::root() const {
  return root_;
}

}  // namespace impdungeon

