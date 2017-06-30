#ifndef HIGH_ELF_H_INCLUDED
#define HIGH_ELF_H_INCLUDED

#include "Elf.h"

#define E_STRENGTH 36
#define E_HITPOINTS 160
#define E_SPEED 80
#define E_PAYOFF 8
#define E_COST 12

class High_elf : public Elf {
    public:
        High_elf();

        virtual void die() const;
        virtual string get_species() const;
};

#endif // HIGH_ELF_H_INCLUDED
