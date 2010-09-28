#include "item.h"

namespace impdungeon {

Item::Item(const boost::uuids::uuid &id, const std::string &name, int value, 
           bool equipable, bool usable)
  : id_(id),
    name_(name),
    value_(value),
    equipable_(equipable),
    usable_(usable) {

}

Item::~Item() {

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
