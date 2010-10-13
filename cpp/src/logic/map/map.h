#ifndef IMPDUNGEON_LOGIC_MAP_MAP_H_
#define IMPDUNGEON_LOGIC_MAP_MAP_H_

#include <string>

#include "logic/map/attributes/position.h"

namespace impdungeon {

class View;

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
  View *GetView(const Position &position, int width, int height) const;

  int width();
  int height();

 private:
  int width_, height_;
  Tile *tiles_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_MAP_MAP_H_

