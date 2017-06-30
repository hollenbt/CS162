#include "library.h"

librarian::librarian() : name(""), id(0) {}

librarian::librarian(const string &s, int i) : name(s), id(i) {}

librarian::librarian(const librarian &li) : name(li.name), id(li.id) {}

librarian::~librarian() {};

librarian& librarian::operator=(const librarian &li) {
    if (&li != this) {
        set_name(li.name);
        set_id(li.id);
    }
    return *this;
}

string& librarian::get_name() {
    return name;
}

int librarian::get_id() const {
    return id;
}

void librarian::set_name(const string &s) {
    name = s;
}

void librarian::set_id(int i) {
    id = i;
}

/*********************************************************************
 ** Function: librarian::change_library_hours
 ** Description: Gets opening and closing hours for each day of the
 **   week, updates the library object and the library hours datafile.
 ** Parameters: library &l - reference to the library object to load
 **               updated hours into.
 **             const string &file - the filepath of the library hours
 **               datafile.
 ** Pre-Conditions: file contains a valid, accessible filepath, otherwise
 **   the program will be terminated.
 ** Post-Conditions: The library's hours of operation have been updated,
 **   both in the week member and in the library hours datafile.
 ** Return: N/A
 *********************************************************************/
void librarian::change_library_hours(library &l, const string &file) {
    ofstream out("./temp.txt");
    check_file(out, "./temp.txt");

    string days[7] = {"Monday: ", "Tuesday: ", "Wednesday: ", "Thursday: ", "Friday: ", "Saturday: ", "Sunday: "};
    hours wk[7];
    cout << "Enter space-separated new opening and closing hours for,\n";
    for (int i = 0; i < 7; ++i) {
        do {
            cout << days[i];
            cin >> wk[i].begin_time >> wk[i].end_time;
        } while (!check_24hr_no_colon_time_string(wk[i].begin_time) || !check_24hr_no_colon_time_string(wk[i].end_time));
        out << wk[i].begin_time << "|" << wk[i].end_time << "|";
    }
    out.close();
    remove(file.c_str());
    rename("./temp.txt", file.c_str());
    l.set_hours(wk);
}

/*********************************************************************
 ** Function: librarian::add_new_books
 ** Description: The user is allowed to choose how many different
 **   books to add. Book information is entered manually by the user,
 **   including the number of copies to add. Pre-existing books added
 **   simply increase the number of available copies, while new books
 **   are appended to the end of the file.
 ** Parameters: cart &c - a cart object that books will be added to
 **               and printed using cart::print_books.
 **             const string &file - the filepath of the book database
 **               file.
 ** Pre-Conditions: N/A
 ** Post-Conditions: The new books have been added to the book database
 **   file and the cart has been emptied after use.
 ** Return: N/A
 *********************************************************************/
void librarian::add_new_books(cart &c, const string &file) {
    ofstream out("./temp.txt");
    check_file(out, "./temp.txt");
    ifstream in(file);
    check_file(in, file);

    int add_num;
    get_pos_integer("How many different books would you like to add? ", &add_num);

    book b;
    for (int i = 0; i < add_num; ++i) {
        input_book_manually(b);
        get_pos_integer("Number of copies: ", &b.copies_avail);
        b.copies_out = 0;
       
        c.add_to_cart(b);
        delete[] b.authors;
    }
    
    int index;
    cart temp;
    while (in.peek() != EOF) {
        temp.read_books(in, 0, 1);
        index = c.find_in_cart(temp.get_books()[0]);
        if (index != -1) {
            temp.get_books()[0].copies_avail += c.get_books()[index].copies_avail;
            c.remove_from_cart(index);
        }
        temp.print_books(out, 0, 1);
    }
    c.print_books(out, 0, c.get_num_books());
    c.empty_cart();
    
    in.close();
    out.close();
    remove(file.c_str());
    rename("./temp.txt", file.c_str());
}

/*********************************************************************
 ** Function: librarian::input_book_manually
 ** Description: Gets book information from the user.
 ** Parameters: book &b - a reference to a book in the caller to store
 **               the entered information.
 ** Pre-Conditions: N/A
 ** Post-Conditions: b contains the information entered by the user.
 ** Return: N/A
 *********************************************************************/
void librarian::input_book_manually(book &b) {
    cout << "\nBook title: ";
    getline(cin, b.title);
    get_pos_integer("Number of authors: ", &b.num_authors);
    b.authors = new string[b.num_authors];
    for (int a = 0; a < b.num_authors; ++a) {
        cout << "Author " << a + 1 << ": ";    
        getline(cin, b.authors[a]);
    }
    get_pos_integer("Year of publication: ", &b.year);
}

/*********************************************************************
 ** Function: librarian::remove_old_books
 ** Description: Removes all books in the library published prior to a
 **   user-specified year. This does not affect books currently checked
 **   out by users, but these books will not be added back into the
 **   book database file when returned.
 ** Parameters: cart &c - a cart object that will be used to read in
 **               each book and print the desired books.
 **             const string &file - the filepath of the book database
 **               file.
 ** Pre-Conditions: N/A
 ** Post-Conditions: All books published prior to the specified year
 **   have been removed from the book database file.
 ** Return: N/A
 *********************************************************************/
void librarian::remove_old_books(cart &c, const string &file){
    int year;
    get_pos_integer("Remove all books prior to year: ", &year);
    cout << "Are you sure you want to remove all books prior to " << year << "? (y/n) ";
    char conf;
    cin.get(conf);
    if (conf != 'y')
        return;

    ofstream out("./temp.txt");
    check_file(out, "./temp.txt");
    ifstream in(file);
    check_file(in, file);

    while (in.peek() != EOF) {
        c.read_books(in, 0, 1);
        if (c.get_books()[0].year >= year)
            c.print_books(out, 0, 1);
    }
    in.close();
    out.close();
    remove(file.c_str());
    rename("./temp.txt", file.c_str());
}

/*********************************************************************
 ** Function: librarian::view_books_checked_out
 ** Description: Outputs a menu and calls functions according to user
 **   input indicating how to view checked out books.
 ** Parameters: library &lib - a library object that is a convenient
 **               way to pass both a cart object and a patron object.
 **             const string &bcofile - the filepath of the books
 **               checked out file.
 **             const string &pidfile - the filepath of the patron login
 **               information file.
 ** Pre-Conditions: bcofile and pidfile are valid, accessible filepaths.
 ** Post-Conditions: The user has chosen to return to the librarian menu.
 ** Return: N/A
 *********************************************************************/
void librarian::view_books_checked_out(library &lib, const string &bcofile, const string &pidfile) {
    int choice = -1;
    while (choice != 4) {
        ifstream in(bcofile);
        check_file(in, bcofile);
        string menu = "\nChoose from the following options:\n\t1. View all checked out books.\n\t2. View books checked out by a specific user.\n\t3. View which user(s) have checked out a particular book.\n\t4. Return to the menu.\n\n";
        get_pos_integer(menu, &choice, 4);
        if (choice == 1)
            view_all_books_out(in, lib);
        else if (choice == 2)
            view_specific_user_out(in, lib, pidfile);
        else if (choice == 3)
            view_specific_book_out(in, lib);
    }
}

/*********************************************************************
 ** Function: librarian::view_all_books_out
 ** Description: Prints all checked out books to the console, organized
 **   by patron.
 ** Parameters: ifstream &in - an input file stream object associated
 **               with an opened file from which checked out book
 **               data will be read.
 **             library &lib - a convenient way to pass both a cart
 **               and a patron object.
 ** Pre-Conditions: in is associated with a file opened for reading.
 ** Post-Conditions: All currently checked out books have been printed
 **   to the console, organized by patron.
 ** Return: N/A
 *********************************************************************/
void librarian::view_all_books_out(ifstream &in, library &lib) {
    cart &c = lib.get_c();
    patron &p = lib.get_p();

    bool books_out = false;
    while (in.peek() != EOF) {
        p.read_patron(in);
        if (p.get_books_checked_out()) {
            books_out = true;
            c.read_books(in, 0, p.get_books_checked_out());
            cout << "\nPatron " << p.get_id() << " - " << p.get_name() << endl;
            c.display_books();
            c.empty_cart();
        }
    }
    if (!books_out)
        cout << "No books checked out.\n\n";
}

/*********************************************************************
 ** Function: librarian::view_specific_user_out
 ** Description: Prints all books currently checked out by a user-
 **   specified patron to the console (if the user-specified patron
 **   exists).
 ** Parameters: ifstream &in - an input file stream object associated
 **               with an opened file from which checked out book
 **               data will be read.
 **             library &lib - a convenient way to pass both a cart
 **               and a patron object.
 **             const string &pidfile - the filepath of patron login
 **               information datafile.
 ** Pre-Conditions: in is associated with a file opened for reading.
 ** Post-Conditions: All books currently checked out by the specified
 **   patron have been printed to the console.
 ** Return: N/A
 *********************************************************************/
void librarian::view_specific_user_out(ifstream &in, library &lib, const string &pidfile) {
    if (!lib.patron_login(pidfile))
        return;

    cart &c = lib.get_c();
    patron &p = lib.get_p();
    patron temp;
    bool found = false;

    cout << "\nPatron " << p.get_id() << " - " << p.get_name() << endl;

    while (in.peek() != EOF) {
        temp.read_patron(in);
        c.read_books(in, 0, temp.get_books_checked_out());
        if (temp.get_id() == p.get_id()) {
            found = true;
            c.display_books();
            break;
        }
        c.empty_cart();
    }
    if (!found)
        cout << "No books checked out.\n\n";
}

/*********************************************************************
 ** Function: librarian::view_specific_book_out
 ** Description: Asks the user to manually input book information,
 **   then prints all patrons that currently have a copy of the
 **   specified book checked out.
 ** Parameters: ifstream &in - an input file stream object associated
 **               with an opened file from which checked out book
 **               data will be read.
 **             library &lib - a convenient way to pass both a cart
 **               and a patron object.
 ** Pre-Conditions: in is associated with a file opened for reading.
 ** Post-Conditions: All patrons that currently have a copy of the
 **   specified book have been printed to the console. Alternatively,
 **   the user is notified if no copies are currently checked out (this
 **   includes if the entered book does not exist).
 ** Return: N/A
 *********************************************************************/
void librarian::view_specific_book_out(ifstream &in, library &lib) {
    cart &c = lib.get_c();
    patron &p = lib.get_p();

    book b;
    input_book_manually(b);

    cout << "\nChecked out by:\n";

    bool checked_out = false;
    while (in.peek() != EOF) {
        p.read_patron(in);
        c.read_books(in, 0, p.get_books_checked_out());
        if (c.find_in_cart(b) != -1) {
            cout << "Patron " << p.get_id() << " - " << p.get_name() << endl;
            checked_out = true;
        }
        c.empty_cart();
    }
    if (!checked_out)
        cout << "No copies checked out.\n\n";
}
