#ifndef SIEGE_H
#define SIEGE_H

#include "Task.h"

class Siege : public Task
{
    public:
        Siege(AI& ai, const Loc& target):
        	Task(ai), _target(target) {}
        ~Siege() {}

        virtual void activate();

    private:
    	Loc _target;
};

#endif
