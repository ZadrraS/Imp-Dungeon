#include "logic/map/view.h"

#include <cstddef>

#include "logic/map/attributes/position.h"

namespace impdungeon {

View::View(char *tiles, int width, int height)
  : tiles_(tiles), width_(width), height_(height) {

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

const char *View::tiles() const {
  return tiles_;
}

int View::width() const {
  return width_;
}

int View::height() const {
  return height_;
}

}  // namespace impdungeon

