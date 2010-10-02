#ifndef IMPDUNGEON_MAP_ATTRIBUTES_POSITION_H
#define IMPDUNGEON_MAP_ATTRIBUTES_POSITION_H

namespace impdungeon {

/*-------------------
* Represents the x and y position of objects on the map.
---------------------*/
class Position {
 public:
  Position();
  Position(int x, int y);
  Position(const Position &position);
  virtual ~Position();

  void set_x(int x);
  void set_y(int y);

  int x() const;
  int y() const;

  Position operator+(const Position &arg);
  Position operator-(const Position &arg);
  Position &operator=(const Position &arg);
  Position &operator+=(const Position &arg);
  Position &operator-=(const Position &arg);
  bool operator==(const Position &arg);

 private:
  int x_, y_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_MAP_ATTRIBUTES_POSITION_H

