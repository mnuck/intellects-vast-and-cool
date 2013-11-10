#ifndef MURDER_H
#define MURDER_H

#include "Task.h"
#include "Unit.h"

class Murder //: public Task
{
    public:
        Murder(AI* a_ai): ai(a_ai) {}
        ~Murder() {}

        virtual void action(Unit target);
        AI* ai;
};
#endif
