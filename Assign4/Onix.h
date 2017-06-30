#ifndef ONIX_H
#define ONIX_H

#include "Rock.h"

#ifdef DEBUG
    #define ONIX_EVOLVE_NUM 1
#else
    #define ONIX_EVOLVE_NUM 3
#endif

#define ONIX_NUMBER 5

class Onix : public Rock {
    public:
        Onix();
        Onix* clone();
        char get_code() const;
};

#endif // ONIX_H
