#ifndef TASK_H
#define TASK_H

#include "AI.h"

class Task{
    public:
        Task(AI& ai): _ai(ai) {}
        ~Task() {}

        virtual void action() = 0;

    protected:
        AI& _ai;
};
#endif
