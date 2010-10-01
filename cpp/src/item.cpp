#include "item.h"

#include <boost/uuid/nil_generator.hpp>

namespace impdungeon {

Item::Item(const std::string &name, int value, bool equipable, bool usable)
  : id_(boost::uuids::nil_generator()()),
    name_(name),
    value_(value),
    equipable_(equipable),
    usable_(usable) {

}

Item::~Item() {

}

bool Item::AssignId(const boost::uuids::uuid &id) {
  if (id_.is_nil()) {
    id_ = id;
    return true;
  }
  return false;
}

const boost::uuids::uuid &Item::id() const {
  return id_;
}

const std::string &Item::name() const {
  return name_;
}

int Item::value() const {
  return value_;
}

bool Item::equipable() const {
  return equipable_;
}

bool Item::usable() const {
  return usable_;
}

}  // namespace impdungeon
