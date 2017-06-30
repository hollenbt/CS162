#include "./state_facts.h"
#include <utility>
#include <cstring>

/*********************************************************************
** Function: is_valid_arguments
** Description: Checks that the correct number of command-line arguments
**   were passed, that the correct tags were used and are accompanied by
**   values. If the number of states argument is not a nonzero positive
**   integer, prompts the user to enter a new value until it is.
** Parameters: char *argv[] - the c-style string array of command-line
**               arguments.
**             int argc - the number of command-line arguments.
** Pre-Conditions: N/A
** Post-Conditions: If the number and positioning of command-line arguments
**   was valid, but the number of states was invalid, the number of states
**   is now valid.
** Return: True if the command-line arguments were valid or the number
**   of states was invalid but the program has successfully recovered, and
**   false if the command-line arguments were invalid and the program
**   must terminate.
*********************************************************************/
bool is_valid_arguments(char *argv[], int argc) {
    if (argc != 5 || ((strcmp(argv[1], "-s") || strcmp(argv[3], "-f")) && (strcmp(argv[3], "-s") || strcmp(argv[1], "-f")))) {
        cout << "Invalid command-line arguments." << endl;
        return false;
    }

    if (!strcmp(argv[1], "-f")) {
        swap(argv[1], argv[3]);
        swap(argv[2], argv[4]);
    }

    while (!is_nonzero_pos_integer(argv[2])) {
        cout << "Enter a nonzero, positive integer for the number of states in the file: ";
        cin >> argv[2];
    }

    return true;
}

/*********************************************************************
** Function: create_states
** Description: Dynamically allocated an array of state structs on the
**   heap and return the address.
** Parameters: int num_states - the length of the state array to be
**               allocated.
** Pre-Conditions: num_states is greater than 0.
** Post-Conditions: A state array of size num_states has been allocated
**   on the heap.
** Return: The address of the beginning of the state array.
*********************************************************************/
state* create_states(int num_states) {
    return new state[num_states];
}

/*********************************************************************
** Function: get_state_data
** Description: Reads in state name, population, and counties members
**   from a file.
** Parameters: state *s_data - pointer to a state array.
**             int state_num - the index of s_data to store the data.
**             ifstream &input - the input filestream object to read
**               the data from.
** Pre-Conditions: input is associated with an open file. The next
**   unread data in the file is a state name, population, and number
**   of counties. state_num is a valid index of the s_data array.
** Post-Conditions: name, population, and counties members of
**   s_data[state_num] have been updated with information from the file.
** Return: N/A
*********************************************************************/
void get_state_data(state *s_data, int state_num, ifstream &input) {
    input >> s_data[state_num].name
          >> s_data[state_num].population
          >> s_data[state_num].counties;
}

/*********************************************************************
** Function: create_counties
** Description: Dynamically allocated an array of county structs on the
**   heap and return the address.
** Parameters: int num_counties - the length of the county array to be
**               allocated.
** Pre-Conditions: num_counties is greater than 0.
** Post-Conditions: A county array of size num_counties has been allocated
**   on the heap.
** Return: The address of the beginning of the county array.
*********************************************************************/
county* create_counties(int num_counties) {
    return new county[num_counties];
}

/*********************************************************************
** Function: get_county_data
** Description: Reads in county name, population, avg_income, avg_house,
**   and cities members from a file, and also allocates memory and reads
**   in city names, assigning the address of the array to the city member.
** Parameters: county *c_data - pointer to a county array.
**             int c_num - the index of c_data to store the data.
**             ifstream &input - the input filestream object to read
**               the data from.
** Pre-Conditions: input is associated with an open file. The next
**   unread data in the file is a county name, population, income, house
**   cost, number of counties, and a list of city names. c_num is a valid
**   index of the c_data array.
** Post-Conditions: name, population, avg_income, avg_house, and cities
**   members of c_data[c_num] have been updated with information from the
**   file, and the city member points to a dynamically allocated string
**   array holding the city names from the file.
** Return: N/A
*********************************************************************/
void get_county_data(county *c_data, int c_num, ifstream &input) {
    county &c = c_data[c_num];
    input >> c.name
          >> c.population
          >> c.avg_income
          >> c.avg_house
          >> c.cities;
    c.city = new string[c.cities];
    for (int i = 0; i < c.cities; ++i)
        input >> c.city[i];
}

/*********************************************************************
** Function: delete_info
** Description: Frees all memory allocated for city arrays in each county,
** county arrays in each state, and the state array itself.
** Parameters: state **data - a pointer to the pointer to the state array
**               to be cleaned up.
**             int num_states - the number of states in the array.
** Pre-Conditions: num_states is the number of elements in the array
**   pointed to by *data.
** Post-Conditions: All city, county, and state memory has been freed, and
**   the state pointer in the calling function has been set to 0.
** Return: N/A
*********************************************************************/
void delete_info(state **data, int num_states) {
    state *s = *data;
    for (int i = 0; i < num_states; ++i) {
        for (int j = 0; j < s[i].counties; ++j)
            delete[] s[i].c[j].city;
        delete[] s[i].c;
    }
    delete[] s;
    *data = 0;
}

/*********************************************************************
** Function: is_nonzero_pos_integer
** Description: Checking whether a character string represents a
**   nonzero positive integer.
** Parameters: const char *num - the c-style string to check.
** Pre-Conditions: num is a null-terminated c-style string.
** Post-Conditions: N/A
** Return: True if num represents a nonzero positive integer, false
**   otherwise.
*********************************************************************/
bool is_nonzero_pos_integer(const char *num) {
    bool nonzero = false;
    for (int i = 0; i < strlen(num); ++i) {
        if (num[i] >= '0' && num[i] <= '9') {
            if (num[i] != '0')
                nonzero = true;
        }
        else return false;
    }
    return nonzero;
}

/*********************************************************************
** Function: open_input_file
** Description: Attempts to open the file, prompting the user to enter
**   a new filename until the file is opened successfully.
** Parameters: string filename - the name of the file to open.
**             ifstream &input - the input filestream object to be
**               associated with the file.
** Pre-Conditions: N/A
** Post-Conditions: input is associated with an open file.
** Return: N/A
*********************************************************************/
void open_input_file(string filename, ifstream &input) {
    input.open(filename);
    while (!input.is_open()) {
        cout << "Error opening file.\nEnter filename: ";
        cin >> filename;
        input.open(filename);
    }
}

/*********************************************************************
** Function: collect_data
** Description: Reads in data from the file.
** Parameters: state **data - pointer to the pointer in the caller that
**               will point to the allocated state array.
**             int num_states - the number of states with data in the file.
**             ifstream &input - the input filestream object associated
**               with the file to read data from.
** Pre-Conditions: input is associated with an open file. num_states
**   is the number of states with data in the file.
** Post-Conditions: A state array has been dynamically allocated and
**   populated with data from the file. A county array has been allocated
**   for each state and populated with data from the file, including a
**   dynamically allocated list of cities.
** Return: N/A
*********************************************************************/
void collect_data(state **data, int num_states, ifstream &input) {
    *data = create_states(num_states);
    state *s = *data;
    for (int i = 0; i < num_states; ++i) {
        get_state_data(s, i, input);
        s[i].c = create_counties(s[i].counties);
        for (int j = 0; j < s[i].counties; ++j)
            get_county_data(s[i].c, j, input);
    }
}

/*********************************************************************
** Function: prompt_repeat
** Description: Asks the user whether they would like to have another
**   data set analyzed. If so,
** Parameters: bool &again - reference to bool to hold whether the
**               user chose to analyze another data set.
**             int &num_states - reference to int to hold the number of
**               states in the new file, if necessary.
**             string &filename - reference to string to hold the new
**               filename, if necessary.
** Pre-Conditions: N/A
** Post-Conditions: If again is true, num_states holds a nonzero
**   positive integer, and filename holds a new filename.
** Return: N/A
*********************************************************************/
void prompt_repeat(bool &again, int &num_states, string &filename) {
    cout << "Enter any nonzero character to analyze a new data set, 0 to exit: ";
    cin >> again;
    if (again) {
        char s_num_chars[50];
        do {
            cout << "Enter the number of states: ";
            cin >> s_num_chars;
        } while (!is_nonzero_pos_integer(s_num_chars));
        num_states = atoi(s_num_chars);
        cout << "Enter the new filename: ";
        cin >> filename;
    }
}

/*********************************************************************
** Function: conduct_analysis
** Description: Ask the user for the avg_income threshold for that section
**   of the output. Asks user to enter an output filename or indicate
**   that output should be printed to the console.
** Parameters: state *data - the state array.
**             int num_states - the size of the state array.
** Pre-Conditions: data points to an array of size num_states that has
**   been fully populated with data.
** Post-Conditions: The analysis has been performed and output in the
**   designated location.
** Return: N/A
*********************************************************************/
void conduct_analysis(state *data, int num_states) {
    double min_income;
    string filename;

    do {
        if(cin.fail()) {
            cin.clear();
            cin.ignore(32767, '\n');
        }
        cout << "Enter county income above which to display: ";
        cin >> min_income;
    } while (cin.fail() || min_income < 0);
    cout << "Enter name of output file (0 to print to screen): ";
    cin >> filename;

    if (filename[0] != '0' || filename.length() != 1) {
        ofstream output(filename);
        calc_and_output(data, num_states, min_income, output);
    }
    else calc_and_output(data, num_states, min_income, cout);
}

/*********************************************************************
** Function: calc_and_output
** Description: Carries out the analysis by calling a series of functions
**   that each perform one aspect of the analysis.
** Parameters: state *data - the state array.
**             int num_states - the size of the state array.
**             double min_income - county avg_income threshold.
**             ostream &out - reference to the object through which all
**               output will be printed.
** Pre-Conditions: data points to an array of size num_states that has
**   been fully populated with data. out is a reference to cout or an
**   ofstream object associated with an open file.
** Post-Conditions: The analysis has been performed and the results
**   have been printed via out.
** Return: N/A
*********************************************************************/
void calc_and_output(state *data, int num_states, double min_income, ostream &out) {
    state **s;

    set_pointers(&s, data, num_states);
    output_alpha(s, num_states, out);
    output_pop(s, num_states, out);
    above_min_income(s, num_states, min_income, out);
    avg_house_by_state(s, num_states, out);

    delete[] s;
}

/*********************************************************************
** Function: output_pop
** Description: Prints the states and their counties ranked by
**   population in descending order. Also prints the state and county
**   with the largest population.
** Parameters: state **s - array of pointers to states.
**             int num_states - the size of the state pointer array.
**             ostream &out - reference to the object through which all
**               output will be printed.
** Pre-Conditions: s points to an array of size num_states. out is a
**   reference to cout or an ofstream object associated with an open file.
** Post-Conditions: All states and their counties have been printed
**   in descending order by population via out.
** Return: N/A
*********************************************************************/
void output_pop(state **s, int num_states, ostream &out) {
    county **c;
    string biggest;
    int big_pop = 0;

    iterativeMergeSort(s, 0, num_states - 1, sort_by_pop);
    out << "\nStates and their counties ranked by population:\n";
    for (int i = 0; i < num_states; ++i) {
        out << "    " << s[i]->name << endl;
        set_pointers(&c, s[i]->c, s[i]->counties);
        iterativeMergeSort(c, 0, s[i]->counties - 1, sort_by_pop);
        if (c[0]->population > big_pop) {
            biggest = c[0]->name;
            big_pop = c[0]->population;
        }
        for (int j = 0; j < s[i]->counties; ++j)
            out << "        " << c[j]->name << endl;
        delete[] c;
    }
    out << "\nLargest state by population: " << s[0]->name << "\nLargest county by population: " << biggest << endl;
}

/*********************************************************************
** Function: output_alpha
** Description: Prints the states and their counties in alphabetical
**   order.
** Parameters: state **s - array of pointers to states.
**             int num_states - the size of the state pointer array.
**             ostream &out - reference to the object through which all
**               output will be printed.
** Pre-Conditions: s points to an array of size num_states. out is a
**   reference to cout or an ofstream object associated with an open file.
** Post-Conditions: All states and their counties have been printed
**   in alphabetical order via out.
** Return: N/A
*********************************************************************/
void output_alpha(state **s, int num_states, ostream &out) {
    county **c;
    iterativeMergeSort(s, 0, num_states - 1, sort_alphabetic);
    out << "\nStates and their counties ranked alphabetically:\n";
    for (int i = 0; i < num_states; ++i) {
        out << "    " << s[i]->name << endl;
        set_pointers(&c, s[i]->c, s[i]->counties);
        iterativeMergeSort(c, 0, s[i]->counties - 1, sort_alphabetic);
        for (int j = 0; j < s[i]->counties; ++j)
            out << "        " << c[j]->name << endl;
        delete[] c;
    }
}

/*********************************************************************
** Function: above_min_income
** Description: Prints all counties with avg_income above a threshold.
** Parameters: state **s - array of pointers to states.
**             int num_states - the size of the state pointer array.
**             double min_income - county avg_income threshold.
**             ostream &out - reference to the object through which all
**               output will be printed.
** Pre-Conditions: s points to an array of size num_states. out is a
**   reference to cout or an ofstream object associated with an open file.
** Post-Conditions: All counties with avg_income members above min_income,
**   but none others, have been printed via out.
** Return: N/A
*********************************************************************/
void above_min_income(state **s, int num_states, double min_income, ostream &out) {
    out << "\nCounties with average income above " << min_income << ":\n";
    for (int i = 0; i < num_states; ++i) {
        for (int j = 0; j < s[i]->counties; ++j)
            if (s[i]->c[j].avg_income > min_income)
                out << "    " << s[i]->c[j].name << endl;
    }
}

/*********************************************************************
** Function: avg_house_by_state
** Description: Calculates and outputs a population-weighted average
**   house cost among all counties for each state.
** Parameters: state **s - array of pointers to states.
**             int num_states - the size of the state pointer array.
**             ostream &out - reference to the object through which all
**               output will be printed.
** Pre-Conditions: s points to an array of size num_states. out is a
**   reference to cout or an ofstream object associated with an open file.
** Post-Conditions: The population-weighted average house cost of each
**   state has been output via out.
** Return: N/A
*********************************************************************/
void avg_house_by_state(state **s, int num_states, ostream &out) {
    out << "\nAverage house price by state:\n";
    double sum_house_pop, sum_pop;
    for (int i = 0; i < num_states; ++i) {
        sum_house_pop = 0;
        sum_pop = 0;
        for (int j = 0; j < s[i]->counties; ++j) {
            sum_house_pop += s[i]->c[j].avg_house * s[i]->c[j].population;
            sum_pop += s[i]->c[j].population;
        }
        out << "    " << s[i]->name << " " << static_cast<int>(sum_house_pop / sum_pop) << endl;
    }
}

/*********************************************************************
** Function: set_pointers
** Description: Allocates an array of struct pointers, and assigns each
**   element the address of the corresponding element of an array of
**   structs. This allows addresses to be swapped during sorting, rather
**   than entire structs.
** Parameters: T ***p - points to a pointer in the caller that will point
**               to the allocated array of pointers.
**             T *data - points to an array of structs.
**             int n - the size of the struct array.
** Pre-Conditions: data is a struct array of size n.
** Post-Conditions: *p points to a dynamically allocated array of
**   pointers that hold the addresses of the corresponding elements of
**   data.
** Return: N/A
*********************************************************************/
template<typename T>
void set_pointers(T ***p, T *data, int n) {
    *p = new T*[n];
    for (int i = 0; i < n; ++i)
        (*p)[i] = data + i;
}

/*********************************************************************
** Function: merge
** Description: Merges two adjacent sorted subarrays into one sorted
**   subarray (with size equal to the sum of the two original sizes).
** Parameters: T *A - the array to be sorted.
**             int l - the start index of the first subarray.
**             int m - the end index of the first subarray.
**             int r - the end index of the second subarray.
**             bool (*comparisonFcn)(T, T) - the boolean function that
**               determines sorted order.
** Pre-Conditions: A points to an array of size at least r + 1.
**   Subarrays A[l] to A[m] and A[m + 1] to A[r] are sorted according
**   to comparisonFcn.
** Post-Conditions: Subarray A[l] to A[r] is sorted according to
**   comparisonFcn.
** Return: N/A
*********************************************************************/
template<typename T>
void merge(T *A, int l, int m, int r, bool (*comparisonFcn)(T, T)) {
    int n1 = m - l + 1;
    int n2 = r - m;
    T *L = new T[n1];
    T *R = new T[n2];

    for (int a = 0; a < n1; ++a)
        L[a] = A[l + a];
    for (int b = 0; b < n2; ++b)
        R[b] = A[m + 1 + b];


    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (comparisonFcn(L[i], R[j]))
            A[k++] = L[i++];
        else A[k++] = R[j++];
    }

    while (i < n1)
        A[k++] = L[i++];

    while (j < n2)
        A[k++] = R[j++];

    delete[] L;
    delete[] R;
}

/*********************************************************************
** Function: iterativeMergeSort
** Description: Performs an iterative (non-recursive) merge sort on an
**   array or subarray.
** Parameters: T *A - the array to be sorted.
**             int l - the start index of the range to be sorted.
**             int r - the end index of the range to be sorted.
**             bool (*comparisonFcn)(T, T) - the boolean function that
**               determines sorted order.
** Pre-Conditions: A points to an array of size at least r + 1.
** Post-Conditions: A[l] to A[r] is sorted according to comparisonFcn.
** Return: N/A
*********************************************************************/
template<typename T>
void iterativeMergeSort(T *A, int l, int r, bool (*comparisonFcn)(T, T)) {
    int current_size, left_start, mid, right_end;
    for (current_size = 1; current_size < r - l + 1; current_size *= 2) {
        for (left_start = l; left_start + current_size - 1 < r; left_start += 2 * current_size) {
            mid = left_start + current_size - 1;
            right_end = min(left_start + 2 * current_size - 1, r);
            merge(A, left_start, mid, right_end, comparisonFcn);
        }
    }
}

/*********************************************************************
** Function: sort_by_pop
** Description: Compares the population members of two structs of the
**   same type.
** Parameters: T *a - pointer to the first struct.
**             T *b - pointer to the second struct.
** Pre-Conditions: a and b point to initialized structs.
** Post-Conditions: N/A
** Return: True if the population member of a is greater than that of b,
**   false if that of b is greater than that of a. If the two are equal,
**   returns true if the name member of a precedes that of b in
**   alphabetical order, false otherwise.
*********************************************************************/
template<typename T>
bool sort_by_pop(T *a, T *b) {
    if (a->population > b->population)
        return true;
    if (a->population < b->population)
        return false;
    return sort_alphabetic(a, b);
}

/*********************************************************************
** Function: sort_alphabetic
** Description: Compares the name members of two structs of the
**   same type.
** Parameters: T *a - pointer to the first struct.
**             T *b - pointer to the second struct.
** Pre-Conditions: a and b point to initialized structs.
** Post-Conditions: N/A
** Return: True if the name member of a precedes that of b in alphabetical
**   order, false if that of b precedes that of a. If the names are
**   identical up to the end of the shorter name, returns true if the
**   name member of a is shorter than that of b, false otherwise.
*********************************************************************/
template<typename T>
bool sort_alphabetic(T *a, T *b) {
    for (int i = 0; i < min(a->name.length(), b->name.length()); ++i) {
        if (a->name[i] < b->name[i])
            return true;
        if (a->name[i] > b->name[i])
            return false;
    }
    return a->name.length() < b->name.length();
}
