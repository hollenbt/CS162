#ifndef CYBERDEMON_H_INCLUDED
#define CYBERDEMON_H_INCLUDED

#include "Demon.h"

#define C_STRENGTH 60
#define C_HITPOINTS 300
#define C_SPEED 40
#define C_PAYOFF 16
#define C_COST 20

class Cyberdemon : public Demon {
    public:
        Cyberdemon();

        virtual void die() const;
        virtual string get_species() const;

};

#endif // CYBERDEMON_H_INCLUDED
