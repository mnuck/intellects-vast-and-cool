#ifndef MURDER_H
#define MURDER_H

#include "Task.h"
#include "Unit.h"
#include "AI.h"

class Murder: public Task
{
    public:
        Murder(AI& ai, Unit& target, Dood type): 
        	Task(ai), _target(target), _doodType(type) {}
        ~Murder() {}

        virtual void activate();

    private:
    	Unit& _target;
    	Dood _doodType;
};
#endif
