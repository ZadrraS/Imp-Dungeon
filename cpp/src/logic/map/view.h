#ifndef IMPDUNGEON_LOGIC_MAP_VIEW_H_
#define IMPDUNGEON_LOGIC_MAP_VIEW_H_

namespace impdungeon {

class Position;

class View {
 public:
  View(char *tiles, int width, int height);
  virtual ~View();

  void Update(char *tiles);

  char GetTile(const Position &position) const;

  int width() const;
  int height() const;

 private:
  char *tiles_;
  int width_;
  int height_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_MAP_VIEW_H_
