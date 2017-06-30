#ifndef CREATURE_H_INCLUDED
#define CREATURE_H_INCLUDED

#include <ctime>
#include "validation_library.h"
using namespace std;

class Creature {
    protected:
        int strength;
        int hitpoints;
        int speed;
        double payoff;
        double cost;

        Creature(int, int, int, double, double);

    public:
        // Accessor functions
        int get_strength() const;
        int get_hitpoints() const;
        int get_speed() const;
        double get_payoff() const;
        double get_cost() const;

        virtual int get_damage();
        bool take_damage(int);
        virtual void die() const;
        virtual double get_winnings(double) const;
        virtual string get_species() const;
};

#endif // CREATURE_H_INCLUDED
