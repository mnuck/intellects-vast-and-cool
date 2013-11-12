#include "Trench.h"

void Trench::action(Loc ice, Loc pump)
{
  std::vector<Loc> path;
  Loc target;
  int shortestPathLength = 1000;
  Unit* bestUnit = NULL;
  int bestUnitId = -1;

  path = ai->bfs(_ice, _pump, Water::PATHABLE, 0);

  for (Loc i : path)
  {
    for (Tile t : ai->tiles)
    {
      if (i.x() == t.x() && i.y() == t.y())
      {
        if (t.depth() == 0)
        {
          target = i;
          goto diggin;
        }
        break;
      }
    }
  }
  diggin:

  for (Unit u: ai->units)
  {
      if (u.touched)
      {
          continue;
      }
      if (u.owner() != ai->playerID())
      {
          continue;
      }

      path = ai->bfs(Loc(u.x(), u.y()),
                     Loc(target.x(), target.y()),
                     Water::BLOCKS, u.maxMovement());

      if (path.size() < shortestPathLength)
      {
          bestUnitId = u.id();
          shortestPathLength = path.size();
      }
  }

  if (bestUnitId == -1)
      return;

  for (int i=0 ; i < (ai->units).size() ; ++i)
  {
      if (ai->units[i].id() == bestUnitId)
      {
          bestUnit = &(ai->units[i]);
          break;
      }
  }

  bestUnit->touched = true;
  path = ai->bfs(Loc(bestUnit->x(), bestUnit->y()),
                 Loc(target.x(), target.y()),
                 Water::BLOCKS, bestUnit->maxMovement());


  for (int i = 0 ; i < bestUnit->maxMovement() && i < path.size() ; ++i)
  {
    bestUnit->move(path[i].x(), path[i].y());
  }
  if (bestUnit->x() == target.x() && bestUnit->y() == target.y())
  {
    for (Tile t : ai->tiles)
    {
      if (target.x() == t.x() && target.y() == t.y())
      {
        bestUnit->dig(t);
        return;
      }
    }
  }
}


