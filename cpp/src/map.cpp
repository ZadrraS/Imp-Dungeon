#include "Map.h"

#include <ifstream>

namespace impdungeon {

Map::Map() {
  tiles_ = NULL;
}

Map::~Map() {
  if (tiles_ != NULL)
    delete [] tiles_;
}

void Map::Init(std::string file_name) {
  std::ifstream file(file_name, std::ifstream::in);
  file >> width_ >> height_;
  tiles = new Tile [width_ * height_];
  for (int y = 0; y < height_; y++) {
    for (int x = 0; x < width_; x++) {
      char tile_rep;
      file >> tile_rep;
      if (tile_rep == '#')
         tiles[y * width_ + x] = WALL;
      else if (tile_rep == '~')
        tiles[y * width_ + x] = WATER;
      else
        tiles[y * width_ + x] = GROUND;

      //  TODO(ZadrraS): Error checking
    }
  }
}

bool Map::IsPassable(const Position &position) const {
  if (tiles(position) != GROUND)
    return true;

  return false;
}

Tile Map::tile(const Position &position) const {
  if (position.x() > 0 && position.y() > 0 &&
     position.x() < width_ && position.y() < height_) {
    return tiles_[position.y() * width_ + position.x()];
  }
  else {
    //  TODO(ZadrraS): Throw exception LOL
  }
}

int Map::width() {
  return width_;
}

int Map::height() {
  return height_;
}

}  // namespace impdungeon

