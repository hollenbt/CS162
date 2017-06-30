#ifndef BLANK_H
#define BLANK_H

#include "Event.h"

class Blank : public Event {
    public:
        Blank* clone() const;
        int percept() const;
        char get_code() const;
        int perform_event(Trainer&);
};

#endif // BLANK_H
