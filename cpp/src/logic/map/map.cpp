#include "logic/map/map.h"

#include "logic/map/view.h"

namespace impdungeon {

Map::Map(int width, int height, Tile *tiles) 
  : width_(width), height_(height), tiles_(tiles) {

}

Map::~Map() {
  if (tiles_ != NULL)
    delete [] tiles_;
}

bool Map::IsPassable(const Position &position) const {
  if (GetTile(position) == kGround)
    return true;

  return false;
}

Tile Map::GetTile(const Position &position) const {
  if (position.x() >= 0 && position.y() >= 0 &&
      position.x() < width_ && position.y() < height_) {
    return tiles_[position.y() * width_ + position.x()];
  }
  else {
    return kNonTile;
  }
}

View *Map::GetView(const Position &position, int width, int height) const {
  char *view_data = new char [width * height];

  int radius_x = (width - 1)/2;
  int radius_y = (height - 1)/2;

  Position pos_it(position.x() - radius_x, position.y() - radius_y);

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      Tile tile = GetTile(pos_it);
      pos_it.set_x(pos_it.x() + 1);

      switch (tile) {
        case kNonTile: {
          view_data[y * width + x] = ' ';
          break;
        }
        case kGround: {
          view_data[y * width + x] = '.';
          break;
        }
        case kWater: {
          view_data[y * width + x] = '~';
          break;
        }
        case kWall: {
          view_data[y * width + x] = '#';
          break;
        }
        default: {
          view_data[y * width + x] = '#';          
          break;
        }
      }
    }
    pos_it.set_x(position.x() - radius_x);
    pos_it.set_y(pos_it.y() + 1);
  }

  return new View(view_data, width, height, 
                  Position(position.x() - radius_x, position.y() - radius_y));
}

int Map::width() {
  return width_;
}

int Map::height() {
  return height_;
}

}  // namespace impdungeon

