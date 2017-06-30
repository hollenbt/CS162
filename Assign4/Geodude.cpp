#include "Geodude.h"

// Non-default Constructor
Geodude::Geodude() : Rock("Geodude", GEODUDE_NUMBER, GEODUDE_EVOLVE_NUM) {}

Geodude* Geodude::clone() {
    return new Geodude(*this);
}

char Geodude::get_code() const {
    return 'G';
}
