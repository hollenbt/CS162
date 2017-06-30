#ifndef DEMON_H_INCLUDED
#define DEMON_H_INCLUDED

#include "Creature.h"

class Demon : public Creature {
    protected:
        Demon(int, int, int, double, double);
    public:
        virtual int get_damage();
};

#endif // DEMON_H_INCLUDED
