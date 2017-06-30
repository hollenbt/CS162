#include "list.h"
#include "math.h"
#include "string.h"

bool check_args(int, char*[], int*, int*, int*, int*);
int poisson_knuth(double);
int get_rand_range(int, int);

void init_list_array(struct list**, int);
void add_to_shortest(struct list*, int, int);
void delete_list_array(struct list**, int);

int main(int argc, char *argv[]) {
    int i, j, arrivals, serve_time;
    int n = 0, s = 0, e = 0, c = 0;
    int *cashiers_mega, *cashiers_array;
    struct list *queue_array, mega_queue;

    if (!check_args(argc, argv, &n, &s, &e, &c)) {
        printf("Invalid command-line arguments.\n");
        return -1;
    }

    srand(time(NULL));
    init(&mega_queue);
    init_list_array(&queue_array, n);

    cashiers_mega = malloc(sizeof(int) * n);
    cashiers_array = malloc(sizeof(int) * n);

    for (i = 0; i < 601; ++i) {
        arrivals = poisson_knuth(1.0 / c);
        while (arrivals--) {
            serve_time = get_rand_range(s, e);
            push_back(&mega_queue, serve_time);
            add_to_shortest(queue_array, n, serve_time);
        }

        for (j = 0; j < n; ++j) {
            if (--cashiers_mega[j] <= 0)
                cashiers_mega[j] = remove_front(&mega_queue);
            if (--cashiers_array[j] <= 0)
                cashiers_array[j] = remove_front(queue_array + j);
        }

        if (i == 60 || i == 300 || i == 600) {
            printf("After %d hour(s):\n", i / 60);
            printf("\tMega-Queue: %d\n\n", size(mega_queue));
            printf("\tMulti-Queues:\n");
            for (j = 0; j < n; ++j)
                printf("\t\t%d: %d\n", j + 1, size(queue_array[j]));
            printf("\n");
        }
    }

    free(cashiers_mega);
    free(cashiers_array);
    delete(&mega_queue);
    delete_list_array(&queue_array, n);

    return 0;
}

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

int poisson_knuth(double lambda) {
    int k = 0;
    double p = 1.0, L = exp(-lambda);
    do {
        ++k;
        p *= ((double) rand() + 1) / ((double) RAND_MAX + 1);
    } while (p > L);
    return k - 1;
}

int get_rand_range(int s, int e) {
    return rand() % (e - s + 1) + s;
}

void init_list_array(struct list **arr, int n) {
    int i;
    *arr = malloc(sizeof(struct list) * n);
    for (i = 0; i < n; ++i)
        init(*arr + i);
}

void add_to_shortest(struct list *arr, int n, int serve_time) {
    int i, min = RAND_MAX, min_i = 0;
    for (i = 0; i < n; ++i)
        if (min > size(arr[i])) {
            min = size(arr[i]);
            min_i = i;
        }
    push_back(arr + min_i, serve_time);
}

void delete_list_array(struct list **arr, int n) {
    int i;
    for (i = 0; i < n; ++i)
        delete(*arr + i);
    free(*arr);
    *arr = NULL;
}
