#ifndef SEIGE_H
#define SEIGE_H

#include "Task.h"

class Seige : public Task
{
    public:
        Seige(AI& ai): Task(ai) {}
        ~Seige() {}

        virtual void activate();
};

#endif
