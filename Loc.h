#ifndef LOC_H
#define LOC_H

#include "Mappable.h"

class Loc
{
public:
  Loc();
  Loc(int a_x, int a_y);
  Loc(const Loc& other);
  Loc(const Mappable& other);

  bool operator==(const Loc& rhs) const;
  bool operator!=(const Loc& rhs) const;
  bool operator<(const Loc& rhs) const;
  Loc operator+(const Loc& rhs) const;

  int x() const;
  int y() const;

private:
  int _x;
  int _y;
};


int manhattanDistance(Loc start, Loc end);

namespace std {
  template <> struct hash<Loc>
  {
    size_t operator()(const Loc & rhs) const
    {
      return rhs.y() * 40 + rhs.x();
    }
  };
}

#endif // LOC_H
