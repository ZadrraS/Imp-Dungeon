#include "map/attributes/position.h"

namespace impdungeon {

Position::Position() : x_(0), y_(0) {

}

Position::Position(int x, int y) : x_(x), y_(y) {

}

Position::Position(const Position &position) : x_(position.x_), y_(position.y_) {

}

Position::~Position() {

}

void Position::set_x(int x) {
  this->x_ = x;
}

void Position::set_y(int y) {
  this->y_ = y;
}

int Position::x() const {
  return x_;
}

int Position::y() const {
  return y_;
}

Position Position::operator+(const Position &arg) {
  Position new_position(this->x_ + arg.x_, this->y_ + arg.y_);
  return new_position;
}

Position Position::operator-(const Position &arg) {
  Position new_position(this->x_ - arg.x_, this->y_ - arg.y_);
  return new_position;
}

Position &Position::operator=(const Position &arg) {
  x_ = arg.x_;
  y_ = arg.y_;
  return *this;
}

Position &Position::operator+=(const Position &arg) {
  x_ += arg.x_;
  y_ += arg.y_;
  return *this;
}

Position &Position::operator-=(const Position &arg) {
  x_ -= arg.x_;
  y_ -= arg.y_;
  return *this;
}

bool Position::operator==(const Position &arg) {
  if (x_ == arg.x_ && y_ == arg.y_)
    return true;

  return false;
}

}  // namespace impdungeon

