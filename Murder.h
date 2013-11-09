#ifndef MURDER_H
#define MURDER_H

#include "Task.h"

class Murder : public Task
{
    public:
        Murder() {}
        ~Murder() {}

        virtual void action();
};
#endif
