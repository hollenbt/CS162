#include "cart.h"

// Default Constructor
cart::cart() : books(0), num_books(0) {}

// Non-default Constructor
cart::cart(book *b, int nb) {
    set_books(b, nb);
}

// Copy Constructor
cart::cart(const cart &c) {
    set_books(c.books, c.num_books);
}

// Destructor
cart::~cart() {
    delete_books();    
}

// Assignment Operator Overload
cart& cart::operator=(const cart &c) {
    if (&c != this)
        set_books(c.books, c.num_books);
    return *this;
}

// Accessor Functions
book* cart::get_books() {
    return books;
}

int cart::get_num_books() const {
    return num_books;
}

// Mutator Functions
void cart::set_books(const book *b, int nb) {
    if (books)
        delete_books();
    
    set_num_books(nb);
    books = new book[nb];
    copy_books(b, nb);
}

void cart::set_num_books(int nb) {
    num_books = nb;
}

/*********************************************************************
 ** Function: cart::delete_books
 ** Description: Removes all books from the cart, freeing the memory
 **   of the string array of authors of each book, as well as the
 **   memory of the book array. Both books and num_books members are
 **   set to 0.
 ** Parameters: N/A
 ** Pre-Conditions: N/A
 ** Post-Conditions: The cart has been reset to the state of carts
 **   immediately after being created with the default constructor.
 ** Return: N/A
 *********************************************************************/
void cart::delete_books() {
    for (int i = 0; i < num_books; ++i)
        delete[] books[i].authors;
    delete[] books;
    books = 0;
    num_books = 0;
}

/*********************************************************************
 ** Function: cart::copy_books
 ** Description:
 ** Parameters: const book *b - a pointer to an array of books to be
 **               copied from.
 **             int nb - the number of books to copy.
 **             int start - the index of the cart's books member to
 **               begin copying into.
 ** Pre-Conditions: b points to an array of books containing at least
 **   nb books. The cart's books member points to an array of books
 **   containing at least start + nb elements.
 ** Post-Conditions: The first nb books of b have been copied into the
 **   cart's books member, starting at index start.
 ** Return: N/A
 *********************************************************************/
void cart::copy_books(const book *b, int nb, int start) {
    for (int i = 0; i < nb; ++i) {
        books[start + i].title = b[i].title;
        books[start + i].num_authors = b[i].num_authors;
        books[start + i].authors = new string[books[start + i].num_authors];
        for (int j = 0; j < books[start + i].num_authors; ++j)
            books[start + i].authors[j] = b[i].authors[j];
        books[start + i].year = b[i].year;
        books[start + i].copies_avail = b[i].copies_avail;    
        books[start + i].copies_out = b[i].copies_out;    
    }
}

/*********************************************************************
 ** Function: cart::read_books
 ** Description: Reads books from a file into the cart's books member.
 ** Parameters: ifstream &in - the file to read from.
 **             int start_index - the index of the cart's books member
 **               to begin reading into.
 **             int num_b - the number of books to read in.
 ** Pre-Conditions: in is associated with a file opened for reading.
 ** Post-Conditions: nb books have been read into the cart's books
 **   member, starting at index start_index. The cart's books member
 **   has been resized if necessary.
 ** Return: N/A
 *********************************************************************/
void cart::read_books(ifstream &in, int start_index, int num_b) {
    if (start_index + num_b > num_books)
        resize_books(start_index + num_b);

    char pipe_eater;
    for (int b = start_index; b < start_index + num_b; ++b) {
        getline(in, books[b].title, '|');
        in >> books[b].num_authors;
        in.get(pipe_eater);

        if(books[b].authors)
            delete[] books[b].authors;
        books[b].authors = new string[books[b].num_authors];
        for (int i = 0; i < books[b].num_authors; ++i)
            getline(in, books[b].authors[i], '|');

        in >> books[b].year;
        in.get(pipe_eater);
        in >> books[b].copies_avail;
        in.get(pipe_eater);
        in >> books[b].copies_out;
        in.get(pipe_eater);
    }
}

/*********************************************************************
 ** Function: cart::print_books
 ** Description: Prints books to a file (or the console) in a pipe ('|')
 **   delimited format.
 ** Parameters: ostream &out - the output stream to print books to.
 **             int start_index - the index of the cart's books member
 **               to begin printing from.
 **             int num_b - the number of books to print.
 ** Pre-Conditions: out is associated with an initialized output stream.
 ** Post-Conditions: If there are less than start_index + num_b books
 **   in the cart's books member, an erro message is printed and no
 **   books are printed. Otherwise, num_b books from the cart's books
 **   member are printed to out, starting at index start_index.
 ** Return: N/A
 *********************************************************************/
void cart::print_books(ostream &out, int start_index, int num_b) const {
    if (start_index + num_b > num_books) {
        cout << "Not enough books to print." << endl;
        return;
    }
    for (int b = start_index; b < start_index + num_b; ++b) {
        out << books[b].title << '|' << books[b].num_authors << '|';
        for (int i = 0; i < books[b].num_authors; ++i)
            out << books[b].authors[i] << '|';
        out << books[b].year << '|' << books[b].copies_avail << '|' << books[b].copies_out << '|';
    }    
}

/*********************************************************************
 ** Function: cart::resize_books
 ** Description: Resizes the cart's books member, managing the dynamic
 **   memory and copying as many books from the original array  into the
 **   resized array as possible (all of them if the size is increased).
 ** Parameters: int s - the new size of the cart's books member.
 ** Pre-Conditions: N/A
 ** Post-Conditions: The books member has been resized to contain s
 **   elements. As many books from the original array as possible have
 **   been copied into the resized array. The num_books member has been
 **   set to s.
 ** Return: N/A
 *********************************************************************/
void cart::resize_books(int s) {
    book *temp = books;
    books = new book[s] {};
    int num_copy = ((s > num_books) ? num_books : s);
    copy_books(temp, num_copy);
    for (int i = 0; temp != 0 && i < num_books; ++i)
        delete[] temp[i].authors;
    delete[] temp;
    num_books = s;
}

/*********************************************************************
 ** Function: cart::add_to_cart
 ** Description: Increases the size of the cart's books member by one
 **   and copies the supplied book into the new (final) element.
 ** Parameters: const book &b - the book to add.
 ** Pre-Conditions: N/A
 ** Post-Conditions: The size of the books member has been increased
 **   by one and b has been copied into the final element.
 ** Return: N/A
 *********************************************************************/
void cart::add_to_cart(const book &b) {
    resize_books(num_books + 1);
    copy_books(&b, 1, num_books - 1);
}

/*********************************************************************
 ** Function: cart::remove_from_cart
 ** Description: Removes a book from the cart's books member, reducing
 **   the size of the array by one and the num_books member
 **   (assuming the books member is not a null pointer and the requested
 **   index is a valid).
 ** Parameters: int i - the index of the book to remove.
 ** Pre-Conditions: N/A
 ** Post-Conditions: If i is a valid index, the book has been removed
 **   from the books member, which has been decreased in size by one,
 **   and the num_books member has been decremented.
 ** Return: N/A
 *********************************************************************/
void cart::remove_from_cart(int i) {
    if (books == 0 || i >= num_books)
        return;
    
    book *temp = books;
    books = new book[num_books - 1];
    copy_books(temp, i);
    copy_books(temp + i + 1, num_books - (i + 1), i);
    for (int j = 0; j < num_books; ++j)
        delete[] temp[j].authors;
    delete[] temp;
    --num_books;
}

/*********************************************************************
 ** Function: cart::find_in_cart
 ** Description: Searches the cart for a certain book, returning the
 **   index if found.
 ** Parameters: const book &b - the book to look for.
 ** Pre-Conditions: N/A
 ** Post-Conditions: N/A
 ** Return: The index of books that matches b, -1 if not found.
 *********************************************************************/
int cart::find_in_cart(const book &b) {
    for (int i = 0; i < num_books; ++i) {
        if (books[i].title == b.title && books[i].num_authors == b.num_authors) {
            bool auth_match = true;
            for (int a = 0; a < b.num_authors; ++a) {
                if (books[i].authors[a].compare(b.authors[a]) != 0) {
                    auth_match = false;
                    break;
                }
            }
            if (auth_match && books[i].year == b.year)
                return i;
        }
    }
    return -1;
}

/*********************************************************************
 ** Function: cart::display_books
 ** Description: Prints all of the books in the cart to the console.
 ** Parameters: N/A
 ** Pre-Conditions: N/A
 ** Post-Conditions: All of the books in the cart have been printed
 **   to the console, numbered such that the book at index i is numbered
 **   i + 1 in the output.
 ** Return: N/A
 *********************************************************************/
void cart::display_books() const {
    for (int i = 0; i < num_books; ++i) {
        cout << '\n' << i + 1 << ".\tTitle: " << books[i].title << endl;
        cout << "\tAuthors: " << books[i].authors[0] << endl;
        for (int a = 1; a < books[i].num_authors; ++a)
            cout << "\t\t " << books[i].authors[a] << endl;
        cout << "\tYear of Publication: " << books[i].year << endl;
        cout << "\tAvailable Copies: " << books[i].copies_avail << endl;
        cout << "\tCopies on Loan: " << books[i].copies_out << endl;
    }
}

/*********************************************************************
 ** Function: cart::empty_cart
 ** Description: Calls delete_books to remove all books from the cart.
 ** Parameters: N/A
 ** Pre-Conditions: N/A
 ** Post-Conditions: The cart has been reset to the state of carts
 **   immediately after being created by the default constructor.
 ** Return: N/A
 *********************************************************************/
void cart::empty_cart() {
    delete_books();
}
