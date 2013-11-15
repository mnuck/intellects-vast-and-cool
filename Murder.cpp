#include <iostream>
#include "Murder.h"
#include "AI.h"

using std::cout;
using std::endl;


void Murder::activate()
{
    int shortestPathLength = 1000;
    std::vector<Loc> path;
    Unit* bestUnit = NULL;
    int bestUnitId = -1;

    Water waterBlocking = Water::PATHABLE;
    if (_doodType == Dood::WORKER)
    {
        waterBlocking = Water::BLOCKS;
    }

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
        if (u.type() != _doodType)
        {
            continue;
        }

        path = _ai.bfs(u, _target, waterBlocking, u.maxMovement());

        if (path.size() < shortestPathLength)
        {
            bestUnitId = u.id();
            shortestPathLength = path.size();
        }
    }

    if (bestUnitId == -1)
    {
        _ai.requestSpawn(_doodType, Loc(_target));
        return;
    }

    bestUnit = _ai.unitIdIndex[bestUnitId];

    bestUnit->touched = true;
    path = _ai.bfs(*bestUnit, _target, 
                   waterBlocking, bestUnit->maxMovement());

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
