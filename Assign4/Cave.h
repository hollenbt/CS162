#ifndef CAVE_H
#define CAVE_H

#include "Event.h"


class Cave : public Event {
    public:
        Cave* clone() const;
        int percept() const;
        char get_code() const;
        int perform_event(Trainer&);
};

#endif // CAVE_H
