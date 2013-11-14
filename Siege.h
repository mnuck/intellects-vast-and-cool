#ifndef SIEGE_H
#define SIEGE_H

#include "Task.h"

class Siege : public Task
{
    public:
        Siege(AI& ai): Task(ai) {}
        ~Siege() {}

        virtual void activate();
};

#endif
