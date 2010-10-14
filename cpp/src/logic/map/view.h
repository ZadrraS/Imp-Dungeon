#ifndef IMPDUNGEON_LOGIC_MAP_VIEW_H_
#define IMPDUNGEON_LOGIC_MAP_VIEW_H_

#include "logic/map/attributes/position.h"

namespace impdungeon {

class Position;

class View {
 public:
  View(char *tiles, int width, int height, const Position &position);
  virtual ~View();

  void Update(char *tiles);

  char GetTile(const Position &position) const;
  Position TranslateGlobal(const Position &global_position);

  const char *tiles() const;
  int width() const;
  int height() const;
  Position position() const;

 private:
  char *tiles_;
  int width_;
  int height_;
  Position position_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_MAP_VIEW_H_

