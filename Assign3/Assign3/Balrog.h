#ifndef BALROG_H_INCLUDED
#define BALROG_H_INCLUDED

#include "Demon.h"

#define B_STRENGTH 20
#define B_HITPOINTS 200
#define B_SPEED 100
#define B_PAYOFF 16
#define B_COST 20

class Balrog : public Demon {
    public:
        Balrog();

        virtual int get_damage();
        virtual void die() const;
        virtual string get_species() const;
};

#endif // BALROG_H_INCLUDED
