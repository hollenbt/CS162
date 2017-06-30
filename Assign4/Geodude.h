#ifndef GEODUDE_H
#define GEODUDE_H

#include "Rock.h"

#ifdef DEBUG
    #define GEODUDE_EVOLVE_NUM 1
#else
    #define GEODUDE_EVOLVE_NUM 3
#endif

#define GEODUDE_NUMBER 3

class Geodude : public Rock {
    public:
        Geodude();
        Geodude* clone();
        char get_code() const;
};

#endif // GEODUDE_H
