#ifndef TRENCH_H
#define TRENCH_H

#include "Task.h"

class Trench : public Task
{
    public:
        Trench() {}
        ~Trench() {}

        virtual void action();
};
#endif
