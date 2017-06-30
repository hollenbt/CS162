/*********************************************************************
 ** Program Filename: compiler.c
 ** Author: Tommy Hollenberg
 ** Date: 06/05/2017
 ** Description: Validates bracket-type punctuation usage in code strings,
 **   ignoring all charaters aside from "[]{}()".
 ** Input: Strings of "code" to be validated for proper bracketing.
 ** Output: Judgment on the validity of the code strings.
 *********************************************************************/

#include "list.h"
#include <string.h>

void get_input(char**);
bool check_validity(char*);

/*********************************************************************
 ** Function: main
 ** Description: Prompts the user to enter a code string, gets user
 **   input, checks the string's bracketing usage, and outputs the result.
 **   Loops until the user enters "quit".
 ** Parameters: N/A
 ** Pre-Conditions: N/A
 ** Post-Conditions: The user chose to quit.
 ** Return: 0
 *********************************************************************/ 
int main() {
    int i = 0;
    char *code = NULL;
    while (1) {
        printf("Enter a character string to check: ");
        get_input(&code);
        if (!strcmp(code, "quit"))
            break;
        if (check_validity(code))
            printf("Valid\n\n");
        else printf("Invalid\n\n");
    }
    free(code);
    code = NULL;
    return 0;
}

/*********************************************************************
 ** Function: get_input
 ** Description: Accepts a string of characters from the user, allocates
 **   the required amount of memory and stores the character string.
 ** Parameters: char **str - a pointer to the character pointer in the
 **               caller that will point to the dynamically allowed
 **               memory holding the user-input string.
 ** Pre-Conditions: N/A
 ** Post-Conditions: The memory pointed to by *str has been deallocated,
 **   and new memory has been grown to fit the user entered character
 **   string.
 ** Return: N/A
 *********************************************************************/ 
void get_input(char **str) {
    int i, size = 0;
    char ch = 0, *temp;
    free(*str);
    *str = NULL;

    scanf("%c", &ch);
    while (ch != '\n') {
        temp = *str;
        *str = malloc(sizeof(char) * (size + 2));
        for (i = 0; i < size; ++i)
            (*str)[i] = temp[i];
        (*str)[size] = ch;
        (*str)[++size] = '\0';
        free(temp);
        scanf("%c", &ch);
    }

}

/*********************************************************************
 ** Function: check_validity
 ** Description: Checks the validity of the bracketing usage of a code
 **   string. Invalid usage includes closing punctuation not immediately
 **   preceded by the corresponding opening punctuation, and unclosed
 **   opening punctuation.
 ** Parameters: char *code - a pointer to the character string to
 **               validate.
 ** Pre-Conditions: N/A
 ** Post-Conditions: N/A
 ** Return: False if code has invalid bracketing usage, true otherwise.
 *********************************************************************/ 
bool check_validity(char *code) {
    int i = 0;
    bool valid = true;
    struct list stack;
    init(&stack);

    if (code == NULL)
        return false;

    while (code[i] != '\0') {
        // opening punctuation
        if (code[i] == '[')
            push_back(&stack, 0);
        else if (code[i] == '{')
            push_back(&stack, 1);
        else if (code[i] == '(')
            push_back(&stack, 2);
        // closing punctuation
        else if (code[i] == ']') {
            if (pop_back(&stack) != 0)
                valid = false, code[i+1] = '\0';
        }
        else if (code[i] == '}') {
            if (pop_back(&stack) != 1)
                valid = false, code[i+1] = '\0';
        }
        else if (code[i] == ')') {
            if (pop_back(&stack) != 2)
                valid = false, code[i+1] = '\0';
        }
        ++i;
    }
    valid = valid && empty(stack);
    delete(&stack);
    return valid;
}
