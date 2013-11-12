#include <iostream>
#include "Murder.h"
#include "AI.h"

using std::cout;
using std::endl;


void Murder::action()
{
    int shortestPathLength = 1000;
    std::vector<Loc> path;
    Unit* bestUnit = NULL;
    int bestUnitId = -1;

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

        path = _ai.bfs(u, _target, Water::BLOCKS, u.maxMovement());

        if (path.size() < shortestPathLength)
        {
            bestUnitId = u.id();
            shortestPathLength = path.size();
        }
    }

    if (bestUnitId == -1)
        return;

    for (int i=0 ; i < (_ai.units).size() ; ++i)
    {
        if (_ai.units[i].id() == bestUnitId)
        {
            bestUnit = &(_ai.units[i]);
            break;
        }
    }

    bestUnit->touched = true;
    path = _ai.bfs(*bestUnit, _target, 
                   Water::BLOCKS, bestUnit->maxMovement());

    // FIXME: need retreat logic for archers kiting tanks
    int distance = manhattanDistance(*bestUnit, _target);
    if (distance <= bestUnit->range())
    {
        bestUnit->attack(_target);
        return;
    }

    for (int i = 0 ; i < bestUnit->maxMovement() && i < path.size() ; ++i)
    {
        int distance = manhattanDistance(*bestUnit, _target);
        if (distance <= bestUnit->range())
        {
            bestUnit->attack(_target);
            break;
        }
        bestUnit->move(path[i].x(), path[i].y());
    }
}
