#ifndef MOAT_H
#define MOAT_H

#include "Task.h"

class Siege : public Task
{
    public:
        Moat(AI& ai): Task(ai) {}
        ~Moat() {}

        virtual void activate();
};

#endif