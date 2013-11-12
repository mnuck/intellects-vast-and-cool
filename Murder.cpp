#include <iostream>

using std::cout;
using std::endl;

#include "Murder.h"

void Murder::action(Unit target)
{
    int shortestPathLength = 1000;
    std::vector<Loc> path;
    Unit* bestUnit = NULL;
    int bestUnitId = -1;

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
                       true, u.maxMovement());

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
                   true, bestUnit->maxMovement());


    int distance = manhattanDistance(Loc(bestUnit->x(), bestUnit->y()),
                                     Loc(target.x(), target.y()));
    if (distance <= bestUnit->range())
    {
        bestUnit->attack(target);
        return;
    }

    for (int i = 0 ; i < bestUnit->maxMovement() && i < path.size() ; ++i)
    {
        int distance = manhattanDistance(Loc(bestUnit->x(), bestUnit->y()),
                                         Loc(target.x(), target.y()));
        if (distance <= bestUnit->range())
        {
            bestUnit->attack(target);
            break;
        }
        bestUnit->move(path[i].x(), path[i].y());
    }
}


