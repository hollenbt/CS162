#ifndef ESPEON_H
#define ESPEON_H

#include "Psychic.h"

#ifdef DEBUG
    #define ESPEON_EVOLVE_NUM 1
#else
    #define ESPEON_EVOLVE_NUM 3
#endif

#define ESPEON_NUMBER 2

class Espeon : public Psychic {
    public:
        Espeon();
        Espeon* clone();
        char get_code() const;
};

#endif // ESPEON_H
