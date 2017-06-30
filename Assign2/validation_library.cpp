#include "validation_library.h"

/*********************************************************************
 ** Function: check_file
 ** Description: Checks that the input file stream object is associated
 **                with an open file. If not, prints an error message
 **                and termiantes the program.
 ** Parameters: ifstream &in - a reference to the input file stream to
 **               check.
 **             const string &file - the filepath used to initialize the
 **               input file stream object.
 ** Pre-Conditions: N/A
 ** Post-Conditions: in is associated with an open file, or the program
 **   has termianted.
 ** Return: N/A
 *********************************************************************/
void check_file(ifstream &in, const string &file) {
    if (!in.is_open()) {
        cout << "Error opening input file: " << file << endl;
        exit(1);
    }
}

/*********************************************************************
 ** Function: check_file
 ** Description: Checks that the output file stream object is associated
 **                with an open file. If not, prints an error message
 **                and terminates the program.
 ** Parameters: ofstream &out - a reference to the output file stream
 **               to check.
 **             const string &file - the filepath used to initialize
 **               the output file stream object.
 ** Pre-Conditions: N/A
 ** Post-Conditions: out is associated with an open file, or the program
 **   has termianted.
 ** Return: N/A
 *********************************************************************/
void check_file(ofstream &out, const string &file) {
    if(!out.is_open()) {
        cout << "Error opening output file:  " << file << endl;
        exit(1);
    }
}

/*********************************************************************
 ** Function: get_pos_integer
 ** Description: Ouputs a prompt and gets an integer from the user until
 **   the entered value is a positive integer between 1 and the specified
 **   maximum input value.
 ** Parameters: const string &prompt - the prompt to be repeatedly output.
 **             int *val - a pointer to an integer in the caller where
 **               the entered value is stored.
 **             int max_input - the maximum acceptable input value
 **               (INT_MAX by default).
 ** Pre-Conditions: max_input is a positive integer. val is not a null
 **   pointer.
 ** Post-Conditions: val points to an integer between 1 and max_input.
 ** Return: N/A
 *********************************************************************/
void get_pos_integer(const string &prompt, int *val, int max_input) {
    *val = -1;
    while (*val <= 0 || *val > max_input) {
        cout << prompt;
        cin >> *val;
        if (cin.fail()) {
            cin.clear();
            *val = -1;
        }
        cin.ignore(INT_MAX, '\n');
    }
}

/*********************************************************************
 ** Function: get_nonneg_integer
 ** Description: Ouputs a prompt and gets an integer from the user until
 **   the entered value is a non-negative integer between 0 and the specified
 **   maximum input value.
 ** Parameters: const string &prompt - the prompt to be repeatedly output.
 **             int *val - a pointer to an integer in the caller where
 **               the entered value is stored.
 **             int max_input - the maximum acceptable input value
 **               (INT_MAX by default).
 ** Pre-Conditions: max_input is a non-negative integer. val is not a null
 **   pointer.
 ** Post-Conditions: val points to an integer between 0 and max_input.
 ** Return: N/A
 *********************************************************************/
void get_nonneg_integer(const string &prompt, int *val, int max_input) {
    *val = -1;
    while (*val < 0 || *val > max_input) {
        cout << prompt;
        cin >> *val;
        if (cin.fail()) {
            cin.clear();
            *val = -1;
        }
        cin.ignore(INT_MAX, '\n');
    }
}

/*********************************************************************
 ** Function: get_integer_string
 ** Description: Outputs a prompt and gets a string from the user until
 **   the string represents a positive integer number.
 ** Parameters: const string &prompt - the prompt to be repeatedly output.
 **             string &num - a reference to the string object where the
 **               entered integer string is stored.
 ** Pre-Conditions: N/A
 ** Post-Conditions: num holds a string that represents a positive
 **   integer number.
 ** Return: N/A
 *********************************************************************/
void get_integer_string(const string &prompt, string &num) {
    bool valid = true;
    do {
        cout << prompt;
        cin >> num;
        if (num[0] < '1' || num[0] > '9') {
            valid = false;
            continue;
        }
        for (int i = 1; i < num.length(); ++i)
            if (num[i] < '0' || num[i] > '9') {
                valid = false;
                break;
            }
    } while (!valid);
}

/*********************************************************************
 ** Function: check_24hr_no_colon_time_string
 ** Description: Checks whether the passed string is in a valid 24hr time
 **   format (i.e. 0700, 1629, etc.).
 ** Parameters: const string &t - the string to check.
 ** Pre-Conditions: N/A
 ** Post-Conditions: N/A
 ** Return: True if the string is a valid 24hr time string, false otherwise.
 *********************************************************************/
bool check_24hr_no_colon_time_string(const string &t) {
    if (t.length() != 4)
        return false;
    if (t[0] == '0' || t[0] == '1') {
        if (t[1] < '0' || t[1] > '9')
            return false;
    }
    else if (t[0] == '2') {
        if (t[1] < '0' || t[1] > '3') {
            if (t[1] == '4' && t[2] == '0' && t[3] == '0')
                return true;
            return false;
        }
    }
    else return false;

    if (t[2] < '0'|| t[2] > '5' || t[3] < '0' || t[3] > '9')
        return false;
    return true;
}
