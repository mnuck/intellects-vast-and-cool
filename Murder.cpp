#include <iostream>
#include <vector>
#include <algorithm>
#include "Murder.h"
#include "AI.h"

using std::cout;
using std::endl;
using std::vector;

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
                   waterBlocking, bestUnit->maxMovement(),
                   Pathing::RANDOMIZED);

    int distance = manhattanDistance(*bestUnit, _target);
    if (distance < bestUnit->range())
    {
        std::unordered_map<Loc, Loc> blocking = 
            _ai.getBlockingGrid(*bestUnit, waterBlocking,
                                bestUnit->maxMovement());
        vector<Loc> directions = {
            Loc( 0, -1), Loc( 0,  1),
            Loc(-1,  0), Loc( 1,  0)};
        for (int i = 0 ; i < bestUnit->maxMovement() && distance < bestUnit->range() ; ++i)
        {
            std::random_shuffle(directions.begin(), directions.end());
            for (Loc d: directions)
            {
                Loc next = Loc(*bestUnit) + d;
                if (blocking[d] == Loc(-1, -1))
                {
                    int nextDistance = manhattanDistance(next, _target);
                    if (nextDistance > distance)
                    {
                        cout << "MOVING " << bestUnit->id() << " FROM " << bestUnit->x() << " " << bestUnit->y()
                             << " TO " << next.x() << " " << next.y() << endl;
                        bestUnit->move(next.x(), next.y());
                        distance = nextDistance;
                    }
                }
            }
        }
    }

    distance = manhattanDistance(*bestUnit, _target);
    if (distance <= bestUnit->range())
    {
        bestUnit->attack(_target);
        return;
    }

    for (int i = 0 ; i < bestUnit->maxMovement() && i < path.size() ; ++i)
    {
        distance = manhattanDistance(*bestUnit, _target);
        if (distance <= bestUnit->range())
        {
            bestUnit->attack(_target);
            break;
        }
        bestUnit->move(path[i].x(), path[i].y());
    }
}
