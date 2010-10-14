#include "logic/map/view.h"

#include <cstddef>

#include "logic/map/attributes/position.h"
#include <iostream>
namespace impdungeon {

View::View(char *tiles, int width, int height, const Position &position)
  : tiles_(tiles), width_(width), height_(height), position_(position) {

}

View::~View() {
  if (tiles_ != NULL)
    delete [] tiles_;
}

void View::Update(char *tiles) {
  if (tiles != NULL)
    delete [] tiles_;

  tiles_ = tiles;
}

char View::GetTile(const Position &position) const {
  return tiles_[position.y() * width_ + position.x()];
}

Position View::TranslateGlobal(const Position &global_position) {
  return global_position - position_;
}

const char *View::tiles() const {
  return tiles_;
}

int View::width() const {
  return width_;
}

int View::height() const {
  return height_;
}

Position View::position() const {
  return position_;
}

}  // namespace impdungeon

