#ifndef MURDER_H
#define MURDER_H

#include "Task.h"
#include "Unit.h"

class Murder: public Task
{
    public:
        Murder(AI& ai, Unit& target): Task(ai), _target(target) {}
        ~Murder() {}

        virtual void action();

    private:
    	Unit& _target;
};
#endif
