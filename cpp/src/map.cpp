#include "map.h"

#include <fstream>
#include <iostream>

namespace impdungeon {

Map::Map() {
  tiles_ = NULL;
}

Map::~Map() {
  if (tiles_ != NULL)
    delete [] tiles_;
}

void Map::Init(const std::string &file_name) {
  std::ifstream map_file(file_name.c_str());

  map_file >> width_ >> height_;
  tiles_ = new Tile [width_ * height_];
  for (int y = 0; y < height_; y++) {
    for (int x = 0; x < width_; x++) {
      char tile_rep;
      map_file >> tile_rep;
      if (tile_rep == '#')
         tiles_[y * width_ + x] = WALL;
      else if (tile_rep == '~')
        tiles_[y * width_ + x] = WATER;
      else
        tiles_[y * width_ + x] = GROUND;

      //  TODO(ZadrraS): Error checking
    }
  }
}

bool Map::IsPassable(const Position &position) const {
  if (tile(position) != GROUND)
    return true;

  return false;
}

Tile Map::tile(const Position &position) const {
  if (position.x() > 0 && position.y() > 0 &&
     position.x() < width_ && position.y() < height_) {
    return tiles_[position.y() * width_ + position.x()];
  }
  else {
    return NON_TILE;
  }
}

int Map::width() {
  return width_;
}

int Map::height() {
  return height_;
}

}  // namespace impdungeon

