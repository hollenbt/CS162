#ifndef RAYQUAZA_H
#define RAYQUAZA_H

#include "Flying.h"

#ifdef DEBUG
    #define RAYQUAZA_EVOLVE_NUM 1
#else
    #define RAYQUAZA_EVOLVE_NUM 3
#endif

#define RAYQUAZA_NUMBER 6

class Rayquaza : public Flying {
    public:
        Rayquaza();
        Rayquaza* clone();
        char get_code() const;;
};

#endif // RAYQUAZA_H
