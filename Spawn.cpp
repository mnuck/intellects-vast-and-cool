#include <iostream>
#include "Spawn.h"
#include "AI.h"
#include "Loc.h"

using std::cout;
using std::endl;


void Spawn::activate()
{
    int shortestPathLength = 1000;
    std::vector<Loc> path;
    int bestTileId = -1;

    Water waterBlocking = Water::PATHABLE;
    if (_doodType == Dood::WORKER)
    {
        waterBlocking = Water::BLOCKS;
    }

	// if I don't have enough oxy, bail
    int oxyAvailable = _ai.players[_ai.playerID()].oxygen();
    int cost = _ai.unitTypes[_doodType].cost();
    if (oxyAvailable < cost)
    {
        return;
    }

    for (Tile t: _ai.tiles)
    {
        bool covered = false;
        if (t.owner() != _ai.playerID())
        {
            continue;
        }
        if (t.isSpawning())
        {
            continue;
        }
        for (Unit u: _ai.units)
        {
            if (Loc(u) == Loc(t))
            {
                covered = true;
                break;
            }
        }
        if (covered)
        {
            continue;
        }

        if (Loc(t) == _spawnLoc)
        {
            bestTileId = t.id();
            break;
        }

        path = _ai.bfs(t, _spawnLoc, waterBlocking, 0);
        if (path.size() == 0)
        {
            continue;
        }

        if (path.size() < shortestPathLength)
        {
            bestTileId = t.id();
            shortestPathLength = path.size();
        }
    }

    if (bestTileId == -1)
    {
        return;
    }

    for (Tile t: _ai.tiles)
    {
        if (t.id() == bestTileId)
        {
            t.spawn(_doodType);
            return;
        }
    }
}
