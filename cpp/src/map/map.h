#ifndef IMPDUNGEON_MAP_MAP_H_
#define IMPDUNGEON_MAP_MAP_H_

#include <string>

#include "map/attributes/position.h"

namespace impdungeon {

enum Tile {
  kNonTile,
  kGround,
  kWater,
  kWall
};

/*-------------------
* Map stores all static game map information.
---------------------*/
class Map {
 public:
  Map(int width, int height, Tile *tiles);
  virtual ~Map();

  bool IsPassable(const Position &position) const;
  Tile GetTile(const Position &position) const;

  int width();
  int height();

 private:
  int width_, height_;
  Tile *tiles_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_MAP_MAP_H_

