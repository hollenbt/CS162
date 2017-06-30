#ifndef HUMAN_H_INCLUDED
#define HUMAN_H_INCLUDED

#include "Creature.h"

#define H_STRENGTH 50
#define H_HITPOINTS 200
#define H_SPEED 50
#define H_PAYOFF 6
#define H_COST 10

class Human : public Creature {
    public:
        Human();

        virtual void die() const;
        virtual double get_winnings(double) const;
        virtual string get_species() const;
};

#endif // HUMAN_H_INCLUDED
