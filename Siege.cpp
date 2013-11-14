#include "Siege.h"

void Siege::activate() 
{
	int shortestPathLength = 1000;
    std::vector<Loc> path;
    Unit* bestUnit = NULL;
    int bestUnitId = -1;

    for (int i=2 ; --i)
    {
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
	        if (u.type() != i)
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
	    if (bestUnitId != -1)
	    {
	    	continue
	    }
    }
 
    if (bestUnitId == -1)
    {
        _ai.requestSpawn(_doodType, Loc(_target));
        return;
    }

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
                   waterBlocking, bestUnit->maxMovement());
}
