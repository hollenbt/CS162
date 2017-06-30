#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED

#include "patron.h"
#include "librarian.h"

class library {
    private:
        hours week[7];
        cart c;
        librarian l;
        patron p;

    public:
        library();
        library(hours*, const cart&, const librarian&, const patron&);
        library(const library&);
        ~library();
        library& operator=(const library&);

        hours* get_hours();
        cart& get_c();
        librarian& get_l();
        patron& get_p();
        void set_hours(const hours*);
        void set_c(const cart&);
        void set_l(const librarian&);
        void set_p(const patron&);

        bool patron_login(const string&);
        bool librarian_login(const string&);
        void display_daily_hours(const string&);
        void display_weekly_hours();
};

#endif // LIBRARY_H_INCLUDED
