#include "Onix.h"

// Non-default Constructor
Onix::Onix() : Rock("Onix", ONIX_NUMBER, ONIX_EVOLVE_NUM) {}

Onix* Onix::clone() {
    return new Onix(*this);
}

char Onix::get_code() const {
    return 'O';
}
