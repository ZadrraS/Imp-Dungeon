 #include "map/attributes/boundedattribute.h"

namespace impdungeon {

BoundedAttribute::BoundedAttribute(int value) : value_(value), bound_(value) {

}

BoundedAttribute::BoundedAttribute(int value, int bound)
  : value_(value),
    bound_(bound) {

}

BoundedAttribute::~BoundedAttribute() {

}

int BoundedAttribute::value() {
  return value_;
}

int BoundedAttribute::bound() {
  return bound_;
}

BoundedAttribute BoundedAttribute::operator+(int arg) {
  int new_value = 0;
  if (value_ + arg > bound_)
    new_value = bound_;
  else
    new_value = value_ + arg;

  BoundedAttribute new_attribute(new_value);
  return new_attribute;
}

BoundedAttribute BoundedAttribute::operator-(int arg) {
  BoundedAttribute new_attribute(value_ - arg);
  return new_attribute;
}

BoundedAttribute &BoundedAttribute::operator+=(int arg) {
  if (value_ + arg > bound_)
    value_ = bound_;
  else
    value_ = value_ + arg;

  return *this;
}

BoundedAttribute &BoundedAttribute::operator-=(int arg) {
  value_ -= arg;
  return *this;
}

BoundedAttribute &BoundedAttribute::operator=(int arg) {
  if (arg > bound_)
    value_ = bound_;
  else
    value_ = arg;

  return *this;
}

}  // namespace impdungeon

