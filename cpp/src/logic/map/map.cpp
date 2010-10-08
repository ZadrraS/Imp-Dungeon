#include "logic/map/map.h"

namespace impdungeon {

Map::Map(int width, int height, Tile *tiles) 
  : width_(width), height_(height), tiles_(tiles) {

}

Map::~Map() {
  if (tiles_ != NULL)
    delete [] tiles_;
}

bool Map::IsPassable(const Position &position) const {
  if (GetTile(position) != kGround)
    return true;

  return false;
}

Tile Map::GetTile(const Position &position) const {
  if (position.x() > 0 && position.y() > 0 &&
     position.x() < width_ && position.y() < height_) {
    return tiles_[position.y() * width_ + position.x()];
  }
  else {
    return kNonTile;
  }
}

int Map::width() {
  return width_;
}

int Map::height() {
  return height_;
}

}  // namespace impdungeon

