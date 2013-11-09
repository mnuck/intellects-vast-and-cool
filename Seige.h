#ifndef SEIGE_H
#define SEIGE_H

#include "Task.h"

class Seige : public Task
{
    public:
        Seige() {}
        ~Seige() {}

        virtual void action();
};

#endif
