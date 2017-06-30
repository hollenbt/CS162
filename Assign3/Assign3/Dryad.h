#ifndef DRYAD_H_INCLUDED
#define DRYAD_H_INCLUDED

#include "Elf.h"

#define D_STRENGTH 24
#define D_HITPOINTS 240
#define D_SPEED 60
#define D_PAYOFF 10
#define D_COST 15

class Dryad : public Elf {
    public:
        Dryad();

        void set_health(int);
        virtual int get_damage();
        virtual void die() const;
        virtual string get_species() const;
};

#endif // DRYAD_H_INCLUDED
