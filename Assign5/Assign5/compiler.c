#include "list.h"
#include <string.h>

void get_input(char**);
bool check_validity(char*);

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
