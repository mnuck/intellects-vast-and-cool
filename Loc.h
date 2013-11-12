#ifndef LOC_H
#define LOC_H

#include "Mappable.h"

class Loc
{
public:
  Loc(): _x(-2), _y(-2) {}
  Loc(int a_x, int a_y): _x(a_x), _y(a_y) {}
  Loc(const Loc& other): _x(other._x), _y(other._y) {}
  Loc(const Mappable& other): _x(other.x()), _y(other.y()) {}

  bool operator==(const Loc& rhs) const
  {
    return _x == rhs._x && _y == rhs._y;
  }

  bool operator!=(const Loc& rhs) const
  {
    return !(*this == rhs);
  }

  bool operator<(const Loc& rhs) const
  {
    int myIndex = _y * 40 + _x;
    int hisIndex = rhs._y * 40 + rhs._x;
    return myIndex < hisIndex;
  }

  Loc operator+(const Loc& rhs) const
  {
    Loc result;
    result._x = _x + rhs._x;
    result._y = _y + rhs._y;
    return result;
  }

  int x() const { return _x; }
  int y() const { return _y; }
private:
  int _x;
  int _y;
};


int manhattanDistance(Loc start, Loc end);


#endif // LOC_H
