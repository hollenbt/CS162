#ifndef PROF_H
#define PROF_H

#include "Event.h"


class Prof : public Event {
    public:
        Prof* clone() const;
        int percept() const;
        char get_code() const;
        int perform_event(Trainer&);
};

#endif // PROF_H
