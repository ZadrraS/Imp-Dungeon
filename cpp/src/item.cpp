#include "item.h"

namespace impdungeon {

Item::Item(const boost::uuids::uuid &id, const std::string &name, int value)
  : id_(id),
    name_(name),
    value_(value) {

}

Item::~Item() {

}

const boost::uuids::uuid &Item::id() {
  return id_;
}

const std::string &Item::name() {
  return name_;
}

int Item::value() {
  return value_;
}

}  // namespace impdungeon
