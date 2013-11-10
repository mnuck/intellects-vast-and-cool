#ifndef TASK_H
#define TASK_H

#include "AI.h"
#include "Mappable.h"
#include "Unit.h"
#include <vector>

class Task{
    public:
        Task()
        : numUnits(0)
        , obj()
        , ai(NULL)
        {}

        ~Task() {}

        virtual void action() = 0;

    protected:
        unsigned numUnits;
        Mappable obj;
        AI* ai;
};
#endif
