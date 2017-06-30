#ifndef MEWTWO_H
#define MEWTWO_H

#include "Psychic.h"

#ifdef DEBUG
    #define MEWTWO_EVOLVE_NUM 1
#else
    #define MEWTWO_EVOLVE_NUM 3
#endif

#define MEWTWO_NUMBER 4

class Mewtwo : public Psychic {
    public:
        Mewtwo();
        Mewtwo* clone();
        char get_code() const;
};

#endif // MEWTWO_H
