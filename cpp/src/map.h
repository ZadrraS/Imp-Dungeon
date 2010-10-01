#ifndef IMPDUNGEON_MAP_H_
#define IMPDUNGEON_MAP_H_

#include <string>

#include "position.h"

namespace impdungeon {

enum Tile {
  NON_TILE,
  GROUND,
  WATER,
  WALL
};

/*-------------------
* Map stores all static game map information.
---------------------*/
class Map {
 public:
  Map();
  virtual ~Map();

  void Init(const std::string &file_name);

  bool IsPassable(const Position &position) const;
  Tile tile(const Position &position) const;

  int width();
  int height();

 private:
  int width_, height_;
  Tile *tiles_;
};

}  // namespace imp_dungeon

#endif  // IMPDUNGEON_MAP_H_

