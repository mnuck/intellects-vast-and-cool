#ifndef DEFEND_H
#define DEFEND_H

#include "Task.h"

class Defend : public Task
{
    public:
        Defend() {}
        ~Defend() {}

        virtual void action();
};
#endif
