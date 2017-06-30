#include "Location.h"
#include <algorithm>

// Default Constructor
Location::Location() : event(0) {}

// Non-default Constructor
Location::Location(Event *e) : event(e) {}

// Copy Constructor
Location::Location(Location &l) : event(l.event->clone()) {}

Location::~Location() {
    delete event;
}
// Assignment Operator Overload
Location& Location::operator=(Location l) {
    swap(event, l.event);
    return *this;
}

// Accessors
Event* Location::get_event() {
    return event;
}

// Mutators
void Location::set_event(Event *e) {
    event = e;
}
