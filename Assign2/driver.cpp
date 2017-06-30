/*********************************************************************
 ** Program Filename: driver.cpp
 ** Author: Thomas Hollenberg
 ** Date: 04/23/2017
 ** Description: Simulates an online library system.
 ** Input: Users must sign in with a valid id, and must enter input to
 **   control program operation.
 ** Output: Writes all data to five files, which are #define-d for
 **   ease of renaming.
 *********************************************************************/

#include "library.h"
#include <fstream>

#define PATRON_IDs "./data/patron_id.lib.txt"
#define LIBRARIAN_IDs "./data/librarian_id.lib.txt"
#define LIB_HOURS "./data/library_hours.lib.txt"
#define BOOK_DATABASE "./data/book_database.lib.txt"
#define BOOKS_CHECKED_OUT "./data/books_checked_out.lib.txt"

library* load_lib_hours(const string&);
void patron_menu(library*);
void librarian_menu(library*);

/*********************************************************************
 ** Function: main
 ** Description: Prints the main menu and calls functions according to
 **   user choices. Loops until user chooses to exit.
 ** Parameters: N/A
 ** Pre-Conditions: N/A
 ** Post-Conditions: Data files have been updated to reflect actions
 **   taken while the program was running.
 ** Return: 0
 *********************************************************************/
int main() {
    cout << "\nWelcome to the Online Library!\n";
    library *lib = load_lib_hours(LIB_HOURS);

    int choice = -1;
    while (choice != 5) {
        string menu = "\nPlease choose from the following menu options:\n\t1. Login as patron.\n\t2. Login as librarian.\n\t3. View library hours for the entire week.\n\t4. View library hours for a specific day.\n\t5. Exit\n\n";
        get_pos_integer(menu, &choice, 5);
        if (choice == 1) {
            if(lib->patron_login(PATRON_IDs))
                patron_menu(lib);
        }
        else if (choice == 2) {
            if(lib->librarian_login(LIBRARIAN_IDs))
                librarian_menu(lib);
        }
        else if (choice == 3)
            lib->display_weekly_hours();
        else if (choice == 4) {    
            cout << "Enter day of the week: ";
            string s;
            getline(cin, s);
            lib->display_daily_hours(s);
        }
    }
    
    delete lib;
    return 0;
}

/*********************************************************************
 ** Function: load_lib_hours
 ** Description: Creates a library object on the heap and loads library
 **   hours of operation from a file.
 ** Parameters: const string &file - the file to read hours from.
 ** Pre-Conditions: file is the path of a file containing 14 valid 24-hr
 **   time strings. Otherwise, the program will print an error message
 **   and terminate.
 ** Post-Conditions: The week member of the library object has been
 **   filled with valid hours of operating from the file.
 ** Return: A pointer to the created library object.
 *********************************************************************/
library* load_lib_hours(const string &file) {
    ifstream in(file);
    check_file(in, file);

    hours wk[7];
    for (int i = 0; i < 7; ++i) {
        getline(in, wk[i].begin_time, '|');
        getline(in, wk[i].end_time, '|');
        if (!check_24hr_no_colon_time_string(wk[i].begin_time) || !check_24hr_no_colon_time_string(wk[i].end_time)) {
            cout << "Invalid library hours." << endl;
            exit(2);
        }
    }

    library *l = new library();
    l->set_hours(wk);
    return l;
}

/*********************************************************************
 ** Function: patron_menu
 ** Description: Prints the patron user menu, calling functions according
 **   to user input. Loops until the user chooses to logout.
 ** Parameters: library *lib - a pointer to the library object.
 ** Pre-Conditions: The patron object member of the library object has
 **   been loaded with the current patron's information.
 ** Post-Conditions: All datafiles have been updated to reflect the
 **   actions taken by the user.
 ** Return: N/A
 *********************************************************************/
void patron_menu(library *lib) {
    cout << "Hello, " << lib->get_p().get_name() << "!\n";
    int choice = -1;
    while (choice != 5) {
        string menu = "\nPlease choose from the following menu options:\n\t1. Search for books to add.\n\t2. View/Manage Cart.\n\t3. Checkout.\n\t4. View/Return books checked out.\n\t5. Logout.\n\n";
        get_pos_integer(menu, &choice, 5);
        if (choice == 1)
            lib->get_p().search(lib->get_c(), BOOK_DATABASE);
        else if (choice == 2)
            lib->get_p().manage_cart(lib->get_c(), PATRON_IDs, BOOKS_CHECKED_OUT, BOOK_DATABASE);
        else if (choice == 3)
            lib->get_p().check_out_books(lib->get_c(), PATRON_IDs, BOOKS_CHECKED_OUT, BOOK_DATABASE);
        else if (choice == 4)
            lib->get_p().view_my_books_out(PATRON_IDs, BOOKS_CHECKED_OUT, BOOK_DATABASE);
    }
}

/*********************************************************************
 ** Function: librarian_menu
 ** Description: Prints the librarian user menu, calling functions
 **   according to user input. Loops until the user chooses to logout.
 ** Parameters: library *lib - a pointer to the library object.
 ** Pre-Conditions: The librarian object member of the library object
 **   has been loaded with the current librarian's information.
 ** Post-Conditions: All datafiles have been updated to reflect the
 **   actions taken by the user.
 ** Return: N/A
 *********************************************************************/
void librarian_menu(library *lib) {
    cout << "Hello, " << lib->get_l().get_name() << "!\n";
    int choice = -1;
    while (choice != 5) {
        string menu = "\nPlease choose from the following menu options:\n\t1. Change library hours.\n\t2. Add new books to the library.\n\t3. Remove old books from the library.\n\t4. View checked out books.\n\t5. Log out.\n\n";
        get_pos_integer(menu, &choice, 5);
        if (choice == 1)
            lib->get_l().change_library_hours(*lib, LIB_HOURS);
        else if (choice == 2)
            lib->get_l().add_new_books(lib->get_c(), BOOK_DATABASE);
        else if (choice == 3)
            lib->get_l().remove_old_books(lib->get_c(), BOOK_DATABASE);    
        else if (choice == 4)
            lib->get_l().view_books_checked_out(*lib, BOOKS_CHECKED_OUT, PATRON_IDs);
    }
}
