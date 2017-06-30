#ifndef CHARIZARD_H
#define CHARIZARD_H

#include "Flying.h"

#ifdef DEBUG
    #define CHARIZARD_EVOLVE_NUM 1
#else
    #define CHARIZARD_EVOLVE_NUM 3
#endif

#define CHARIZARD_NUMBER 1

class Charizard : public Flying {
    public:
        Charizard();
        Charizard* clone();
        char get_code() const;
};

#endif // CHARIZARD_H
