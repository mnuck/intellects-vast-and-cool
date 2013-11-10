#include <cmath>
#include "Loc.h"

using std::abs;

int manhattanDistance(Loc start, Loc end)
{
  return abs(start.x() - end.x()) + abs(start.y() - end.y());
}
