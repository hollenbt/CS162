#include "library.h"

// Default Constructor
patron::patron() : name(""), id(0), books_checked_out(0) {}

// Non-default Constructor
patron::patron(const string &s, int i, int bco) : name(s), id(i), books_checked_out(bco) {} 

// Copy Constructor
patron::patron(const patron &pa) : name(pa.name), id(pa.id), books_checked_out(pa.books_checked_out) {}

// Destructor
patron::~patron() {}

// Assignment Operator Overload
patron& patron::operator=(const patron &pa) {
    if (&pa != this) {
        set_name(pa.name);
        set_id(pa.id);
        set_books_checked_out(pa.books_checked_out);
    }
    return *this;
}

// Accessor Functions
string& patron::get_name() {
    return name;
}

int patron::get_id() const {
    return id;
}

int patron::get_books_checked_out() const {
    return books_checked_out;
}

// Mutator Functions
void patron::set_name(const string &s) {
    name = s;
}

void patron::set_id(int i) {
    id = i;
}

void patron::set_books_checked_out(int b) {
    books_checked_out = b;
}

/*********************************************************************
 ** Function: patron::search
 ** Description: Until the user chooses to cancel, prints the search menu
 **   to the console. Calls specific search functions according to user
 **   input.
 ** Parameters: cart &c - a reference to the library's cart object member.
 **             const string &file - filepath of the book database.
 ** Pre-Conditions: file contains a valid, accessible filepath.
 ** Post-Conditions: The user has chosen to return to the patron menu.
 ** Return: N/A
 *********************************************************************/
void patron::search(cart &c, const string &file) {
    int choice = -1;
    while (choice != 5) {
        ifstream in(file);
        check_file(in, file);
        string menu = "\n\nHow would you like to search?\n\t1. Search by title.\n\t2. Search by author.\n\t3. Search by year.\n\t4. View all books.\n\t5. Cancel.\n\n";
        get_pos_integer(menu, &choice, 5);
        if (choice == 1)
            search_title(in, c);
        else if (choice == 2)
            search_author(in, c);
        else if (choice == 3)
            search_year(in, c);
        else if (choice == 4)
            view_all_books(in, c);
    }
}

/*********************************************************************
 ** Function: patron::choose_from_results
 ** Description: Allows the user to add books from search results to
 **   their cart (but only if there is at least one copy available) in
**    anticipation of checking them out.
 ** Parameters: cart &results - a reference to the cart object holding
 **               the search results.
 **             cart &c - a reference to the library's cart object
 **               member, to which books will be added.
 ** Pre-Conditions: N/A
 ** Post-Conditions: Books from the search results have been added to
 **   the library's cart object member, if desired (and there is at
 **   least one copy available).
 ** Return: N/A
 *********************************************************************/
void patron::choose_from_results(cart &results, cart &c) {
    if (results.get_num_books() == 0) {
        cout << "No matches found.\n";
        return;
    }
    
    results.display_books();
    cout << "\nEnter book numbers to add books to your cart.\nEnter 0 to return to the search menu.\n\n";
    int choice;
    get_nonneg_integer("Add book number: ", &choice, results.get_num_books());
    while (choice != 0) {
        if (results.get_books()[choice - 1].copies_avail == 0)
            cout << "No copies currently available.\n";
        else if (c.find_in_cart(results.get_books()[choice - 1]) != -1)
            cout << "Book already in cart.\n";
        else {
            c.add_to_cart(results.get_books()[choice - 1]);
            cout << "Book " << choice << " added to cart.\n";
        }
        get_nonneg_integer("Add book number: ", &choice, results.get_num_books());
    } 
}

/*********************************************************************
 ** Function: patron::search_title
 ** Description: Reads in all books in the book database, and add all of
 **   them with a user-specified title to a local cart object.
 ** Parameters: ifstream &in - the file to read in books from.
 **             cart &c - a reference to the library's cart menu object.
 ** Pre-Conditions: in is associated with a file opened for reading.
 ** Post-Conditions: All books in the book database with the specified
 **   title have been added to a local cart, from which the user could
 **   select books to add to the libary's cart member object.
 ** Return: N/A
 *********************************************************************/
void patron::search_title(ifstream &in, cart &c) {
    string t;
    cout << "Title to search for: ";
    getline(cin, t);

    int i = 0;
    cart results;
    while (in.peek() != EOF) {
        results.read_books(in, i, 1);
        if (results.get_books()[i].title.compare(t) == 0)
            ++i;
    }
    if (i != results.get_num_books())
        results.remove_from_cart(i);

    choose_from_results(results, c);
}

/*********************************************************************
 ** Function: patron::search_author
 ** Description: Reads in all books in the book database, and add all of
 **   them with a user-specified author to a local cart object.
 ** Parameters: ifstream &in - the file to read in books from.
 **             cart &c - a reference to the library's cart menu object.
 ** Pre-Conditions: in is associated with a file opened for reading.
 ** Post-Conditions: All books in the book database with the specified
 **   author have been added to a local cart, from which the user could
 **   select books to add to the libary's cart member object.
 ** Return: N/A
 *********************************************************************/
void patron::search_author(ifstream &in, cart &c) {
    string a;
    cout << "Author to search for: ";
    getline(cin, a);

    int i = 0;
    cart results;
    while (in.peek() != EOF) {
        results.read_books(in, i, 1);
        for (int n = 0; n < results.get_books()[i].num_authors; ++n) {
            if (results.get_books()[i].authors[n].compare(a) == 0) {
                ++i;
                break;
            }
        }
    }
    if (i != results.get_num_books())
        results.remove_from_cart(i);

    choose_from_results(results, c); 
}

/*********************************************************************
 ** Function: patron::search_year
 ** Description: Reads in all books in the book database, and add all of
 **   them with a user-specified publication year to a local cart object.
 ** Parameters: ifstream &in - the file to read in books from.
 **             cart &c - a reference to the library's cart menu object.
 ** Pre-Conditions: in is associated with a file opened for reading.
 ** Post-Conditions: All books in the book database with the specified
 **   year have been added to a local cart, from which the user could
 **   select books to add to the libary's cart member object.
 ** Return: N/A
 *********************************************************************/
void patron::search_year(ifstream &in, cart &c) {
    int y;
    get_pos_integer("Publication year to search for: ", &y);

    int i = 0;
    cart results;
    while (in.peek() != EOF) {
        results.read_books(in, i, 1);
        if (results.get_books()[i].year == y)
            ++i;
    }
    if (i != results.get_num_books())
        results.remove_from_cart(i);
        
    choose_from_results(results, c);
}

/*********************************************************************
 ** Function: patron::view_all_books
 ** Description: Reads in all books in the book database and adds them
 **   to a local cart object. This cart is passed to the choose_from_results
 **   function along with the library's cart member object, where the
 **   user's book selections will be stored.
 ** Parameters: ifstream &in - the file to read in books from.
 **             cart &c - a reference to the library's cart member object.
 ** Pre-Conditions: in is associated with a file opened for reading.
 ** Post-Conditions: All books in the book database have been added to
 **   a local cart, from which the user could select books to add to
 **   the libary's cart member object.
 ** Return: N/A
 *********************************************************************/
void patron::view_all_books(ifstream &in, cart &c) {
    cart results;
    int i = 0;
    while (in.peek() != EOF)
        results.read_books(in, i++, 1);
    choose_from_results(results, c);
}

/*********************************************************************
 ** Function: patron::manage_cart
 ** Description: Displays the books currently in the cart (if any). The
**    user can choose to remove books from the cart (in which case the
**    updated cart is displayed and the user is presented with the same
**    options), proceed to checkout, or return to the patron menu.
 ** Parameters: cart &c - a reference to a cart object holding the
 **               books addeded from search results by the user.
 **             const string &pidfile - the filepath of the file
 **               holding the patron login information.
 **             const string &bcofile - the filepath of the file
 **               holding the list of books checked out by each patron.
 **             const string &bdbfile - the filepath of the file
 **               holding the library's book database.
 ** Pre-Conditions: N/A
 ** Post-Conditions: Books have been removed from the cart, if desired.
 **   If the user has chosen to checkout the books, the cart has been
 **   emptied and all relevant datafiles have been updated.
 ** Return: N/A
 *********************************************************************/
void patron::manage_cart(cart &c, const string &pidfile, const string &bcofile, const string &bdbfile) {
    int choice = -1;
    while (choice != 3) {
        if (c.get_num_books() == 0) {
            cout << "Cart is empty.\n\n";
            return;
        }
        cout << "\nBooks in Cart:\n";
        c.display_books();
        string menu = "\nChoose an option:\n\t1. Remove book.\n\t2. Proceed to checkout.\n\t3. Return to menu.\n\n";
        get_pos_integer(menu, &choice, 3);
        if (choice == 1) {
            int rem_ch;
            get_pos_integer("Remove book number: ", &rem_ch, c.get_num_books());
            c.remove_from_cart(rem_ch - 1);
            cout << "Book " << rem_ch << " removed from cart.\n";
        }
        else if (choice == 2) {
            check_out_books(c, pidfile, bcofile, bdbfile);
            return;
        }
    } 
}

/*********************************************************************
 ** Function: patron::read_patron
 ** Description: Reads in the patron's name, id, and books_checked_out
 **   from a file.
 ** Parameters: ifstream &in - the file to read this data from.
 ** Pre-Conditions: in is associated with a file opened for reading.
 ** Post-Conditions: The patron's information has been populated with
 **   data read in from the file.
 ** Return: N/A
 *********************************************************************/
void patron::read_patron(ifstream &in) {
    getline(in, name, '|');
    char pipe_eater;
    in >> id >> pipe_eater;
    in >> books_checked_out >> pipe_eater;
}

/*********************************************************************
 ** Function: patron::print_patron
 ** Description: Prints the patron's information, followed by all of the
 **   books in the cart pointed to, if desired.   
 ** Parameters: ofstream &out - the file where the information should
 **               be printed.
 **             const cart *c - a pointer to a cart holding books to
 **               print out as well. This is a pointer and not a reference
 **               so that a null pointer can be passed in if this feature
 **               is not desired.
 ** Pre-Conditions: out is associated with a file opened for writing.
 ** Post-Conditions: The patron information, as well as any associated
 **   books, has been printed to the file.
 ** Return: N/A
 *********************************************************************/
void patron::print_patron(ofstream &out, const cart *c) const {
    out << name << '|' << id << '|' << books_checked_out << '|';
    if (c != 0)
        c->print_books(out, 0, c->get_num_books());
}

/*********************************************************************
 ** Function: patron::check_out_books
 ** Description: Loans out books to the patron, emptying the cart, and
 **   ensuring that all datafiles are updated to reflect this transaction.
 ** Parameters: cart &c - a reference to a cart object holding the
 **               books being checked out by the patron.
 **             const string &pidfile - the filepath of the file
 **               holding the patron login information.
 **             const string &bcofile - the filepath of the file
 **               holding the list of books checked out by each patron.
 **             const string &bdbfile - the filepath of the file
 **               holding the library's book database.
 ** Pre-Conditions: c contains the books to be checked out.
 ** Post-Conditions: All relevant datafiles, as well as the patron's
 ** books_checked_out member have been updated to reflect the books
 **   being checked out.
 ** Return: N/A
 *********************************************************************/
void patron::check_out_books(cart &c, const string &pidfile, const string &bcofile, const string &bdbfile) {
    update_book_database_file(c, bdbfile, 1);
    
    for (int i =0; i < c.get_num_books(); ++i) {
        c.get_books()[i].copies_avail = 0;
        c.get_books()[i].copies_out = 1;
    }
    books_checked_out += c.get_num_books();

    update_patron_login_file(pidfile);
    update_books_out_file(c, bcofile);

    cout << '\n' << c.get_num_books() << " book(s) checked out.\n" << endl;
    c.empty_cart();
}

/*********************************************************************
 ** Function: patron::update_patron_login_file
 ** Description: Updates the patron login file to reflect books being
 **   checked in or out.
 ** Parameters: const string &pidfile - the filepath of the library's
 **               patron login information file.
 ** Pre-Conditions: The patron's books_checked_out member has already
 **   been updated to reflect the books checked in/out.
 ** Post-Conditions: The patron login file has been updated to reflect
 **   the books being checked in/out.
 ** Return: N/A
 *********************************************************************/
void patron::update_patron_login_file(const string &pidfile) const {
    ofstream out("./temp.txt");
    check_file(out, "./temp.txt");
    ifstream in(pidfile);
    check_file(in, pidfile);

    patron temp_p;
    while (in.peek() != EOF) {
        temp_p.read_patron(in);
        if (id == temp_p.get_id())
            print_patron(out);
        else temp_p.print_patron(out);
    }

    in.close();
    out.close();
    remove(pidfile.c_str());
    rename("./temp.txt", pidfile.c_str());
}

/*********************************************************************
 ** Function: patron::update_books_checked_out__file
 ** Description: Updates the books checked out file to reflect any books
 **   that have been checked in or out.
 ** Parameters: cart &c - a cart holding the books to be checked out
 **               or returned.
 **             const string &bcofile - the filepath of the file
 **               holding the list of books checked out.
 **             bool returning - true if books are being returned, false
 **               if books are being checked out. False by default.
 ** Pre-Conditions: The patron's books checked out member has already
 **   been updated, and c contains the books that are being checked in/out.
 ** Post-Conditions: The books checked out file has been updated to reflect
 **   the books being checked in/out.
 ** Return: N/A
 *********************************************************************/
void patron::update_books_out_file(const cart &c, const string &bcofile, bool returning) const {
    ofstream out ("./temp.txt");
    check_file(out, "./temp.txt");
    ifstream in(bcofile);
    check_file(in, bcofile);

    patron temp_p;
    cart temp_c;
    bool found = false;
    while (in.peek() != EOF) {
        temp_p.read_patron(in);
        temp_c.read_books(in, 0, temp_p.get_books_checked_out());
        if (id == temp_p.get_id()) {
            found = true;
            if (returning)
                print_patron(out, &c);
            else {
                print_patron(out, &temp_c);
                c.print_books(out, 0, c.get_num_books());
            }
        }
        else temp_p.print_patron(out, &temp_c);
        temp_c.empty_cart();
    }
    if (!found)
        print_patron(out, &c);

    in.close();
    out.close();
    remove(bcofile.c_str());
    rename("./temp.txt", bcofile.c_str());
}

/*********************************************************************
 ** Function: patron::update_book_database_file
 ** Description: Updates the book database file to reflect any books
 **   that have been checked in or out.
 ** Parameters: cart &c - a cart holding the books to be checked out
 **               or returned.
 **             const string &bdbfile - the filepath of the library's
 **               book database file.
 **             int in_or_out - an integer indicating whether books
 **               are being checked out (1) or returned (-1).
 ** Pre-Conditions: in_or_out contains a value of 1 or -1, depending
 **   on whether books are being checked out or returned, respectively.
 **   c contains the books that are being checked in/out.
 ** Post-Conditions: The book database file has been updated to reflect
 **   the books being checked in/out.
 ** Return: N/A
 *********************************************************************/
void patron::update_book_database_file(cart &c, const string &bdbfile, int in_or_out) {
    ofstream out ("./temp.txt");
    check_file(out, "./temp.txt");
    ifstream in(bdbfile);
    check_file(in, bdbfile);

    int index;
    cart temp;
    while (in.peek() != EOF) {
        temp.read_books(in, 0, 1);
        index = c.find_in_cart(temp.get_books()[0]);
        if (index != -1) {
            temp.get_books()[0].copies_avail -= in_or_out;
            temp.get_books()[0].copies_out += in_or_out;
        }
        temp.print_books(out, 0, 1);
    }

    in.close();
    out.close();
    remove(bdbfile.c_str());
    rename("./temp.txt", bdbfile.c_str());
}

/*********************************************************************
 ** Function: patron::view_my_books_out
 ** Description: Populates a cart object with the books currently
 **   checked out by the patron, and allows the patron to choose
 **   to return books (while they still have books checked out) or
 **   return to the patron menu.
 ** Parameters: const string &pidfile - the filepath of the file
 **               holding the patron login information.
 **             const string &bcofile - the filepath of the file
 **               holding the list of books checked out by each patron.
 **             const string &bdbfile - the filepath of the file
 **               holding the library's book database.
 ** Pre-Conditions: The patron's id member contains a valid patron id.
 ** Post-Conditions: Any returns requested have been made.
 ** Return: N/A
 *********************************************************************/
void patron::view_my_books_out(const string &pidfile, const string &bcofile, const string &bdbfile) {
    ifstream in(bcofile);
    check_file(in, bcofile);

    cart c;
    patron temp_p;
    while (in.peek() != EOF) {
        temp_p.read_patron(in);
        c.read_books(in, 0, temp_p.get_books_checked_out());
        if (id == temp_p.get_id())
            break;
        c.empty_cart();
    }
    in.close(); 
    
    int choice = -1;
    while (choice != 2) {
        if (c.get_num_books() == 0) {
            cout << "No books checked out.\n\n";
            return;
        }
        cout << "\nBooks checked out:\n";
        c.display_books();
        string menu = "\nChoose an option:\n\t1. Return a book.\n\t2. Return to menu.\n\n";
        get_pos_integer(menu, &choice, 2);
        if (choice == 1)
            return_book(c, pidfile, bcofile, bdbfile);
    }
}

/*********************************************************************
 ** Function: patron::return_book
 ** Description: Prompts the patron to choose a book to return, then
 **   ensures that all relevant datafiles are updated to reflect
 **   that the book has been returned.
 ** Parameters: cart &c - a reference to a cart object holding the
 **               books currently checked out by the patron.
 **             const string &pidfile - the filepath of the file
 **               holding the patron login information.
 **             const string &bcofile - the filepath of the file
 **               holding the list of books checked out by each patron.
 **             const string &bdbfile - the filepath of the file
 **               holding the library's book database.
 ** Pre-Conditions: c holds all of and only the books currently
 **    checked out by the patron.
 ** Post-Conditions: All relevant datafiles, as well as the patron's
 **   books_checked_out member, have been updated to reflect the book
 **   being returned.
 ** Return: N/A
 *********************************************************************/
void patron::return_book(cart &c, const string &pidfile, const string &bcofile, const string &bdbfile) {
    int num;
    get_pos_integer("Return book number: ", &num, c.get_num_books());
    cart temp;
    temp.add_to_cart(c.get_books()[num - 1]);
    c.remove_from_cart(num - 1);

    --books_checked_out;
    update_book_database_file(temp, bdbfile, -1);
    update_patron_login_file(pidfile);
    update_books_out_file(c, bcofile, true);
}
