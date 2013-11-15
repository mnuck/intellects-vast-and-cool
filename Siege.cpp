#include "Siege.h"

void Siege::activate() 
{
    int shortestPathLength = 1000;
    std::vector<Loc> path;
    Unit* bestUnit = NULL;
    int bestUnitId = -1;
    Dood doodType;
    Water waterBlocking;
    
    for (int i = 2 ; i >= 0 ; --i)
    {
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
            if (u.type() != i)
            {
                continue;
            }

            if (Loc(u) == _target)
            {
                bestUnitId = u.id();
                break;
            }

            waterBlocking = Water::PATHABLE;
            if (i == Dood::WORKER)
            {
                waterBlocking = Water::BLOCKS;
            }
       
            path = _ai.bfs(u, _target, waterBlocking, u.maxMovement());

            if (path.size() == 0)
            {
                continue;
            }

            if (path.size() < shortestPathLength)
            {
                bestUnitId = u.id();
                shortestPathLength = path.size();
            }
        }
        if (bestUnitId != -1)
        {
            doodType = Dood(i);
            break;
        }
    }
 
    if (bestUnitId == -1)
    {
        _ai.requestSpawn(Dood::TANK, Loc(_target));
        return;
    }

    bestUnit = _ai.unitIdIndex[bestUnitId];

    bestUnit->touched = true;
    path = _ai.bfs(*bestUnit, _target, 
                   waterBlocking, bestUnit->maxMovement(),
                   Pathing::RANDOMIZED);
    for (int i = 0 ; i < bestUnit->maxMovement() && i < path.size() ; ++i)
    {
        bestUnit->move(path[i].x(), path[i].y());
    }

    // TODO: attack any targets of opportunity
}
