#ifndef ELF_H_INCLUDED
#define ELF_H_INCLUDED

#include "Creature.h"

class Elf : public Creature {
    protected:
        Elf(int, int, int, double, double);
    public:
        virtual int get_damage();
        virtual double get_winnings(double) const;
};

#endif // ELF_H_INCLUDED
