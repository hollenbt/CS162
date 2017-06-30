#ifndef LOCATION_H
#define LOCATION_H

#include "Event.h"

class Location {
    private:
        Event *event;
    public:
        Location();
        Location(Event*);
        Location(Location&);
        ~Location();
        Location& operator=(Location);

        Event* get_event();
        void set_event(Event*);
};

#endif // LOCATION_H
