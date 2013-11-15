#include "Trench.h"
#include "AI.h"

void Trench::activate()
{
  std::vector<Loc> path;
  Loc target;
  int shortestPathLength = 1000;
  Unit* bestUnit = NULL;
  int bestUnitId = -1;

  path = _ai.bfs(_ice, _pump, Water::PATHABLE, 0);

  for (Loc i : path)
  {
    for (Tile t : _ai.tiles)
    {
      if (i == Loc(t))
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

  for (Unit u: _ai.units)
  {
      if (u.touched)
      {
          continue;
      }
      if (u.owner() != _ai.playerID())
      {
          continue;
      }

      path = _ai.bfs(u, target, Water::BLOCKS, u.maxMovement());

      if (path.size() < shortestPathLength)
      {
          bestUnitId = u.id();
          shortestPathLength = path.size();
      }
  }

  if (bestUnitId == -1)
      return;

  bestUnit = _ai.unitIdIndex[bestUnitId];

  bestUnit->touched = true;
  path = _ai.bfs(*bestUnit, target,
                 Water::BLOCKS, bestUnit->maxMovement());


  for (int i = 0 ; i < bestUnit->maxMovement() && i < path.size() ; ++i)
  {
    bestUnit->move(path[i].x(), path[i].y());
  }
  if (Loc(*bestUnit) == target)
  {
    for (Tile t : _ai.tiles)
    {
      if (target == Loc(t))
      {
        bestUnit->dig(t);
        return;
      }
    }
  }
}


