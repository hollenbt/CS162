#ifndef PATRON_H_INCLUDED
#define PATRON_H_INCLUDED

#include "cart.h"

class library;

class patron {
    private:
        string name;
        int id;
        int books_checked_out;
        void choose_from_results(cart&, cart&);
        void search_title(ifstream&, cart&);
        void search_author(ifstream&, cart&);
        void search_year(ifstream&, cart&);
        void view_all_books(ifstream&, cart&);
        void update_patron_login_file(const string&) const;
        void update_books_out_file(const cart&, const string&, bool returning = false) const;
        void update_book_database_file(cart&, const string&, int);

    public:
        patron();
        patron(const string&, int, int bco = 0);
        patron(const patron&);
        ~patron();
        patron& operator=(const patron&);

        string& get_name();
        int get_id() const;
        int get_books_checked_out() const;
        void set_name(const string&);
        void set_id(int);
        void set_books_checked_out(int);

        void read_patron(ifstream&);
        void print_patron(ofstream&, const cart *c = 0) const;
        void search(cart&, const string&);
        void manage_cart(cart&, const string&, const string&, const string&);
        void check_out_books(cart&, const string&, const string&, const string&);
        void view_my_books_out(const string&, const string&, const string&);
        void return_book(cart&, const string&, const string&, const string&);
};

#endif // PATRON_H_INCLUDED
