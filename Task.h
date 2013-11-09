#ifndef TASK_H
#define TASK_H

#include "Mappable.h"
#include "Unit.h"
#include <vector>

class Task{
    public:
        Task()
        : numUnits(0)
        , units()
        , obj() {}

        ~Task() {}

        virtual void action() = 0;

    private:
        unsigned numUnits;
        std::vector<Unit> units;
        Mappable obj;
};
#endif
