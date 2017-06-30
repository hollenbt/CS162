#include "library.h"

// Default Constructor
library::library() : week(), c(), l(), p() {}

// Non-default Constructor
library::library(hours *wk, const cart &ca, const librarian &li, const patron &pa) : c(ca), l(li), p(pa) {
    set_hours(wk);
}

// Copy Constructor
library::library(const library &lib) : c(lib.c), l(lib.l), p(lib.p) {
    set_hours(lib.week);
}

// Destructor
library::~library() {}

// Assignment Operator Overload
library& library::operator=(const library &lib) {
    if (this != &lib) {
        set_hours(lib.week);
        set_c(lib.c);
        set_l(lib.l);
        set_p(lib.p);
    }
    return *this;
}


// Accessor Functions
hours* library::get_hours() {
    return week;
}

cart& library::get_c() {
    return c;
}

librarian& library::get_l() {
    return l;
}

patron& library::get_p() {
    return p;
}

// Mutator Functions
void library::set_hours(const hours *wk) {
    for (int i = 0; i < 7; ++i)
        week[i] = wk[i];
}

void library::set_c(const cart &ca) {
    c = ca;
}
void library::set_l(const librarian &li) {
    l = li;
}

void library::set_p(const patron &pa) {
    p = pa;
}

/*********************************************************************
 ** Function: library::patron_login
 ** Description: Asks the user for a patron login id, searches for
 **   the id in a datafile, and, if found, loads the library's patron
 **   object member with the accompanying information from the file.
 ** Parameters: const string &file - the path of the file to read from.
 ** Pre-Conditions: The file string holds the path of an existing,
 **   accessible file. Otherwise the program will print an error message
 **   and terminate.
 ** Post-Conditions: If the patron id was found, the accompanying
 **   information has been loaded into the library's patron object
 **   member. Otherwise, the user has been notified that the patron
 **   id was not found.
 ** Return: True if the patron login was successful, false otherwise.
 *********************************************************************/
bool library::patron_login(const string &file) {
    ifstream in(file);
    check_file(in, file);

    int id;
    get_pos_integer("Enter patron id: ", &id);
    
    patron pat;
    bool found = false;
    while (in.peek() != EOF) {
        pat.read_patron(in);
        if (id == pat.get_id()) {
            found = true;
            p = pat;
            break;
        }
    }
    if (!found)
        cout << "Patron not found." << endl;;
    return found;
}

/*********************************************************************
 ** Function: library::librarian_login
 ** Description: Asks the user for a librarian login id, searches for
 **   the id in a datafile, and, if found, loads the library's librarian
 **   object member with the accompanying information from the file.
 ** Parameters: const string &file - the path of the file to read from.
 ** Pre-Conditions: The file string holds the path of an existing,
 **   accessible file. Otherwise the program will print an error message
 **   and terminate.
 ** Post-Conditions: If the librarian id was found, the accompanying
 **   information has been loaded into the library's librarian object
 **   member. Otherwise, the user has been notified that the librarian
 **   id was not found.
 ** Return: True if the librarian login was successful, false otherwise.
 *********************************************************************/
bool library::librarian_login(const string &file) {
    ifstream in(file);
    check_file(in, file);

    string id, fid, s;
    bool found = false;
    get_integer_string("Enter librarian id: ", id);
    while (in.peek() != EOF) {
        getline(in, s, '|');
        getline(in, fid, '|');
        if (id.compare(fid) == 0) {
            found = true;
            l.set_id(atoi(id.c_str()));
            l.set_name(s);
            break;
        }
    }
    if (!found)
        cout << "Librarian not found." << endl;;
    return found;
}

/*********************************************************************
 ** Function: library::display_daily_hours
 ** Description: Prints the library's hours of operation on a specific
 **   day.
 ** Parameters: const string &s - a string holding the desired day of
 **   the week.
 ** Pre-Conditions: The library's hours of operation have already been
 **   loaded with valid 24-hr time strings.
 ** Post-Conditions: If s holds a day of the week, the hours of operation
 **   for that day have been printed to the console. Otherwise, the
 **   user is informed that the supplied string was not a valid day
 **   of the week.
 ** Return: N/A
 *********************************************************************/
void library::display_daily_hours(const string &s) {
    if (!s.compare("Monday") || !s.compare("monday"))
        cout << "Monday Hours:\t" << week[0].begin_time << " to " << week[0].end_time << endl;
    else if (!s.compare("Tuesday") || !s.compare("tuesday"))
        cout << "Tuesday Hours:\t" << week[1].begin_time << " to " << week[1].end_time << endl;
    else if (!s.compare("Wednesday") || !s.compare("wednesday"))
        cout << "Wednesday Hours: " << week[2].begin_time << " to " << week[2].end_time << endl;
    else if (!s.compare("Thursday") || !s.compare("thursday"))
        cout << "Thursday Hours:\t" << week[3].begin_time << " to " << week[3].end_time << endl;
    else if (!s.compare("Friday") || !s.compare("Friday"))
        cout << "Friday Hours:\t" << week[4].begin_time << " to " << week[4].end_time << endl;
    else if (!s.compare("Saturday") || !s.compare("saturday"))
        cout << "Saturday Hours:\t" << week[5].begin_time << " to " << week[5].end_time << endl;
    else if (!s.compare("Sunday") || !s.compare("sunday"))
        cout << "Sunday Hours:\t" << week[6].begin_time << " to " << week[6].end_time << endl;
    else cout << "Invalid day of the week." << endl;
}

/*********************************************************************
 ** Function: library::display_weekly_hours 
 ** Description: Prints out the hours of operation for the entire week
 **   stored in the library's week member.
 ** Parameters: N/A
 ** Pre-Conditions: The week object has already been loaded with valid
 **   24-hr time strings.
 ** Post-Conditions: The hours of operation for each day of the week
 **   have been printed to the console.
 ** Return: N/A
 *********************************************************************/
void library::display_weekly_hours() {
    cout << "Library Hours:\nMonday\t\t" << week[0].begin_time << " to " << week[0].end_time << endl; 
    cout << "Tuesday\t\t" << week[1].begin_time << " to " << week[1].end_time << endl;
    cout << "Wednesday\t" << week[2].begin_time << " to " << week[2].end_time << endl; 
    cout << "Thursday\t"<< week[3].begin_time << " to " << week[3].end_time << endl; 
    cout << "Friday\t\t"<< week[4].begin_time << " to " << week[4].end_time << endl; 
    cout << "Saturday\t"<< week[5].begin_time << " to " << week[5].end_time << endl; 
    cout << "Sunday\t\t"<< week[6].begin_time << " to " << week[6].end_time << endl; 
}
