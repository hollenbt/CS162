#ifndef CART_H_INCLUDED
#define CART_H_INCLUDED

#include "structs.h"

class cart {
    private:
        book *books;
        int num_books;
        void resize_books(int);
        void delete_books();
        void copy_books(const book*, int, int start = 0);
    public:
        cart();
        cart(book*, int);
        cart(const cart&);
        ~cart();
        cart& operator=(const cart&);

        book* get_books();
        int get_num_books() const;
        void set_books(const book*, int);
        void set_num_books(int);

        void read_books(ifstream&, int, int);
        void print_books(ostream&, int, int) const;
        void add_to_cart(const book&);
        void remove_from_cart(int);
        int find_in_cart(const book&);
        void display_books() const;
        void empty_cart();
};

#endif // CART_H_INCLUDED
