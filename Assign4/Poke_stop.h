#ifndef POKE_STOP_H
#define POKE_STOP_H

#include "Event.h"

class Poke_stop : public Event {
    public:
        Poke_stop* clone() const;
        int percept() const;
        char get_code() const;
        int perform_event(Trainer&);
};

#endif // POKE_STOP_H
