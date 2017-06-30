#ifndef LIBRARIAN_H_INCLUDED
#define LIBRARIAN_H_INCLUDED

#include "cart.h"

class library;

class librarian {
    private:
        string name;
        int id;
    public:
        librarian();
        librarian(const string&, int);
        librarian(const librarian&);
        ~librarian();
        librarian& operator=(const librarian&);

        string& get_name();
        int get_id() const;
        void set_name(const string&);
        void set_id(int);

        void change_library_hours(library&, const string&);
        void add_new_books(cart&, const string&);
        void input_book_manually(book &b);
        void remove_old_books(cart&, const string&);
        void view_books_checked_out(library&, const string&, const string&);
        void view_all_books_out(ifstream&, library&);
        void view_specific_user_out(ifstream&, library&, const string&);
        void view_specific_book_out(ifstream&, library&);
};

#endif // LIBRARIAN_H_INCLUDED
