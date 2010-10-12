#include "client/view/view.h"

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

char View::GetTile(const Position &position) {
  return tiles_[position.y() * width_ + position.x()];
}

int View::width() const {
  return width_;
}

int View::height() const {
  return height_;
}

}  // namespace impdungeon

