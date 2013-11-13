#ifndef SPAWN_H
#define SPAWN_H

#include "Task.h"
#include "Unit.h"
#include "AI.h"

class Spawn: public Task
{
    public:
        Spawn(AI& ai, const SpawnRequest& req): 
        	Task(ai), _doodType(req._doodType),
        	_spawnLoc(req._spawnLocation) {}
        ~Spawn() {}

        virtual void activate();

    private:
    	Dood _doodType;
    	Loc  _spawnLoc;
};
#endif


//Spawn(*this, req).activate();