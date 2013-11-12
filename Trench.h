#ifndef TRENCH_H
#define TRENCH_H

#include "Task.h"

class Trench: public Task
{
    public:
        Trench(AI& ai, Loc ice, Loc pump): 
        	Task(ai), _ice(ice), _pump(pump) {}
        ~Trench() {}

        virtual void action();
    private:
    	Loc _ice;
    	Loc _pump;
};
#endif
