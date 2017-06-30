/*********************************************************************
 ** Program Filename: queues.c
 ** Author: Tommy Hollenberg
 ** Date: 06/10/2017
 ** Description: This program simulates two queueing systems and
 **   compares their performance, based on how many customers are
 **   waiting, at 1, 5, and 10 hour. (The simulation is performed
 **   at 1 minute intervals.) The first system uses one large queue
 **   that feeds all cashiers, while the second system has a separate
 **   queue for each cashier. Customer arrivals are randomly sampled
 **   from a poisson distribution, and service time for each customer
 **   is an integer randomly generated between two bounds.
 ** Input: The number of cashiers (n), service time lower bound (s),
 **   service time upper bound (e), and average time between customer
 **   arrivals (c). These are passed in as command-line arguments in
 **   any order, but must be immediately preceded by the appropriate
 **   tag (-n, -s, -e, -c).
 ** Output: The program prints the simulation results after 60, 300,
 **   and 600 simulation units, corresponding to 1, 5, and 10 hours.
 *********************************************************************/

#include "list.h"
#include "math.h"
#include "string.h"

bool check_args(int, char*[], int*, int*, int*, int*);
int poisson_knuth(double);
int get_rand_range(int, int);

void init_list_array(struct list**, int);
void add_to_shortest(struct list*, int, int);
void delete_list_array(struct list**, int);

/*********************************************************************
 ** Function: main
 ** Description: Checks the command-line arguments. If valid, runs
 **   a simulation of the two queueing systems with the specified
 **   parameters. Otherwise, notifies the user and exits prematurely.
 ** Parameters: int argc - the number of command-line arguments.
 **             char *argv[] - an array of C-strings containing the
 **               command-line arguments.
 ** Pre-Conditions: N/A
 ** Post-Conditions: The simulation results are printed to the console,
 **   or the command-line arguments have been declared invalid.
 ** Return: -1 if the command-line arguments are invalid. 0 otherwise.
 *********************************************************************/ 
int main(int argc, char *argv[]) {
    int i, j, arrivals, serve_time, multi_total;
    int n = 0, s = 0, e = 0, c = 0;
    int *cashiers_mega, *cashiers_array;
    struct list *queue_array, mega_queue;

    if (!check_args(argc, argv, &n, &s, &e, &c)) {
        printf("Invalid command-line arguments.\n");
        return -1;
    }

    // Seed the RNG and initialize the lists.
    srand(time(NULL));
    init(&mega_queue);
    init_list_array(&queue_array, n);

    // Allocate two cashier arrays.
    cashiers_mega = malloc(sizeof(int) * n);
    cashiers_array = malloc(sizeof(int) * n);

    for (i = 0; i < 601; ++i) {
        // Sample the poisson distribution to determine the number of arrivals in this minute.
        // Pre-determine the customer's service time and add them to each queueing system.
        arrivals = poisson_knuth(1.0 / c);
        while (arrivals--) {
            serve_time = get_rand_range(s, e);
            push_back(&mega_queue, serve_time);
            add_to_shortest(queue_array, n, serve_time);
        }

        // Move the simulation one minute forward by decrementing the remaining service times.
        // If a cashier is available (remaining service time is <= 0), assign them to the
        // customer removed from the front of the queue. If the queue is empty, -1 is returned,
        // so the cashier will still register as being available in the next minute.
        for (j = 0; j < n; ++j) {
            if (--cashiers_mega[j] <= 0)
                cashiers_mega[j] = remove_front(&mega_queue);
            if (--cashiers_array[j] <= 0)
                cashiers_array[j] = remove_front(queue_array + j);
        }

        // In the 60th, 300th, and 600th minute of simulation, print the size of each queue.
        if (i == 60 || i == 300 || i == 600) {
            multi_total = 0;
            printf("After %d hour(s):\n", i / 60);
            printf("\tMega-Queue: %d\n\n", size(mega_queue));
            printf("\tMulti-Queues:\n");
            for (j = 0; j < n; ++j) {
                printf("\t\t%d: %d\n", j + 1, size(queue_array[j]));
                multi_total += size(queue_array[j]);
            }
            printf("\t    Total: %d\n\n", multi_total);
        }
    }

    // Free the memory of the cashier arrays.
    // Empty and free the memory of the queues.
    free(cashiers_mega);
    free(cashiers_array);
    delete(&mega_queue);
    delete_list_array(&queue_array, n);

    return 0;
}

/*********************************************************************
 ** Function: check_args 
 ** Description: Parses the command-line arguments, checking that all
 **   four tags (-n, -s, -e, -c) are present, accompanied by positive
 **   integers, and that s <= e.
 ** Parameters: int argc - the number of command-line arguments.
 **             char *argv[] - the command-line arguments.
 **             int *n - points to integer to store the number of
 **               cashiers.
 **             int *s - points to integer to store minimum possible
 **               service time.
 **             int *e - points to integer to store maximum possible
 **               service time.
 **             int *c - points to integer to store the average time
 **               between customer arrivals.
 ** Pre-Conditions: N/A
 ** Post-Conditions: The command-line arguments have been stored in the
 **   relevant variables in the calling function.
 ** Return: True if the arguments are valid, false otherwise.
 *********************************************************************/ 
bool check_args(int argc, char *argv[], int *n, int *s, int *e, int *c) {
    int i;
    if (argc != 9)
        return false;
    for (i = 1; i < 9; i += 2) {
        if (!strcmp(argv[i], "-n") && !(*n)) {
            if ((*n = atoi(argv[i + 1])) <= 0)
                return false;
        }
        else if (!strcmp(argv[i], "-s") && !(*s)) {
            if ((*s = atoi(argv[i + 1])) <= 0)
                return false;
        }
        else if (!strcmp(argv[i], "-e") && !(*e)) {
            if ((*e = atoi(argv[i + 1])) <= 0)
                return false;
        }
        else if (!strcmp(argv[i], "-c") && !(*c)) {
            if ((*c = atoi(argv[i + 1])) <= 0)
                return false;
        }
        else return false;
    }
    return *s <= *e;
}

/*********************************************************************
 ** Function: poisson_knuth
 ** Description: Generates a random sample from a poisson distribution
 **   based on random samples from a uniform distribution (generated
 **   via the rand() function). The algorithm is attributed to Donald
 **   Knuth on Wikipedia. 
 ** Parameters: double lambda - the expected rate.
 ** Pre-Conditions: lambda is a positive number.
 ** Post-Conditions: N/A
 ** Return: The number of arrivals,
 *********************************************************************/ 
int poisson_knuth(double lambda) {
    int k = 0;
    double p = 1.0, L = exp(-lambda);
    do {
        ++k;
        p *= ((double) rand() + 1) / ((double) RAND_MAX + 1);
    } while (p > L);
    return k - 1;
}

/*********************************************************************
 ** Function: get_rand_range
 ** Description: Generates a random integer between s and e, inclusive.
 ** Parameters: int s - the lower bound.
 **             int e - the upper bound.
 ** Pre-Conditions: s and e are positive integers, where s <= e.
 ** Post-Conditions: N/A
 ** Return: A random integer between s and e, inclusive.
 *********************************************************************/ 
int get_rand_range(int s, int e) {
    return rand() % (e - s + 1) + s;
}

/*********************************************************************
 ** Function: init_list_array
 ** Description: Allocates memory and initializes an array of n list
 **   structs.
 ** Parameters: struct list **arr - a pointer to a struct list pointer
 **               in the caller that will store the addres of the
 **               allocated array.
 **             int n - the size of the array to allocate.
 ** Pre-Conditions: arr points to a null pointer.
 ** Post-Conditions: *arr holds the address of an initialized struct
 ** list array of size n.   
 ** Return: N/A
 *********************************************************************/ 
void init_list_array(struct list **arr, int n) {
    int i;
    *arr = malloc(sizeof(struct list) * n);
    for (i = 0; i < n; ++i)
        init(*arr + i);
}

/*********************************************************************
 ** Function: add_to_shortest
 ** Description: Creates a new node with the specified value and
 **   pushes it onto the back of the shortest list in the array.
 ** Parameters: struct list *arr - a pointer to a pointer to the
 **               struct list array.
 **             int n - the number of struct lists in the array.
 **             int serve_time - how long the customer will take to
 **               be served (the value of the node).
 ** Pre-Conditions: N/A
 ** Post-Conditions: A new node with a value of serve_time has been
 **   pushed onto the back of the shortest list in the array. If there
 **   is a tie, the node is pushed onto the back of the list with the
 **   lowest index.
 ** Return: N/A
 *********************************************************************/ 
void add_to_shortest(struct list *arr, int n, int serve_time) {
    int i, min = RAND_MAX, min_i = 0;
    for (i = 0; i < n; ++i)
        if (min > size(arr[i])) {
            min = size(arr[i]);
            min_i = i;
        }
    push_back(arr + min_i, serve_time);
}

/*********************************************************************
 ** Function: delete_list_array
 ** Description: Frees the memory of the struct list array and points
 **   the pointer in the caller to NULL.
 ** Parameters: struct list **arr - a pointer to a pointer to the
 **               struct list array.
 **             int n - the number of elements in the array
 ** Pre-Conditions: N/A
 ** Post-Conditions: The struct list array has been deallocated and
 **   *arr points to NULL.
 ** Return: N/A
 *********************************************************************/ 
void delete_list_array(struct list **arr, int n) {
    int i;
    for (i = 0; i < n; ++i)
        delete(*arr + i);
    free(*arr);
    *arr = NULL;
}
