#ifndef IMPDUNGEON_LOGIC_MAP_ATTRIBUTES_POSITION_H
#define IMPDUNGEON_LOGIC_MAP_ATTRIBUTES_POSITION_H

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

  bool IsNextTo(const Position &position) const;

  void set_x(int x);
  void set_y(int y);

  int x() const;
  int y() const;

  Position operator+(const Position &arg) const;
  Position operator-(const Position &arg) const;
  Position &operator=(const Position &arg);
  Position &operator+=(const Position &arg);
  Position &operator-=(const Position &arg);
  bool operator==(const Position &arg) const;
  bool operator!=(const Position &arg) const;

 private:
  int x_, y_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_MAP_ATTRIBUTES_POSITION_H

