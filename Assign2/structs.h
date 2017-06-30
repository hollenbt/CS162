#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#include "validation_library.h"

struct hours {
    string begin_time;
    string end_time;
};

struct book {
    string title;
    int num_authors;
    string *authors;
    int year;
    int copies_avail;
    int copies_out;
};

#endif // STRUCTS_H_INCLUDED
