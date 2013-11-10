#ifndef TRENCH_H
#define TRENCH_H

#include "Task.h"

class Trench //: public Task
{
    public:
        Trench(AI* a_ai): ai(a_ai) {}
        ~Trench() {}

        virtual void action(Loc ice, Loc pump);
        AI* ai;
};
#endif
