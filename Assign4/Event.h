#ifndef EVENT_H
#define EVENT_H

#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include "validation_library.h"
using namespace std;

class Trainer;

class Event {
    public:
        virtual ~Event() {};
        virtual Event* clone() const = 0;
        virtual int percept() const = 0;
        virtual char get_code() const = 0;
        virtual int perform_event(Trainer&) = 0;
};

#endif // EVENT_H
