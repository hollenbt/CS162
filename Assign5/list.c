#include "list.h"

void init(struct list *list_ptr) {
    list_ptr->head = NULL;
    list_ptr->tail = NULL;
} //initialize empty list

int size(struct list the_list) {
    int n = 0;
    while (the_list.head != NULL) {
        the_list.head = the_list.head->next;
        ++n;
    }
    return n;
} //return number of nodes in list

void print(struct list the_list) {
    struct node *temp = the_list.head;
    while (temp != NULL) {
        printf("%d ", temp->val);
        temp = temp->next;
    }
    printf("\n");
} //print the values in list

void push_front(struct list *list_ptr, int val) {
    struct node *temp = malloc(sizeof(struct node));
    temp->val = val;
    temp->next = list_ptr->head;
    list_ptr->head = temp;
    if (list_ptr->tail == NULL)
        list_ptr->tail = temp;
} //push to front of list

void push_back(struct list *list_ptr, int val) {
    struct node *temp = malloc(sizeof(struct node));
    temp->val = val;
    temp->next = NULL;
    if (list_ptr->head == NULL)
        list_ptr->head = temp;
    else list_ptr->tail->next = temp;
    list_ptr->tail = temp;
} //push to end of list

int front(struct list the_list) {
    if (the_list.head == NULL)
        return -1;
    return the_list.head->val;
} //returns value at the front of the list

int back(struct list the_list) {
    if (the_list.tail == NULL)
        return -1;
    return the_list.tail->val;
} //returns value at the back of the list

int pop_back(struct list *list_ptr) {
    int val;
    struct node *temp;
    if (list_ptr->head == NULL) // empty list
        return -1;
    temp = list_ptr->head;
    if (temp->next == NULL) { // only one element
        list_ptr->head = NULL;
        list_ptr->tail = NULL;
        val = temp->val;
        free(temp);
    }
    else { // multiple elements
        while (temp->next != list_ptr->tail)
            temp = temp->next;
        temp->next = NULL;
        val = list_ptr->tail->val;
        free(list_ptr->tail);
        list_ptr->tail = temp;
    }
    return val;
} //remove node from back and return value

int remove_front(struct list *list_ptr) {
    int val;
    struct node *temp;
    if (list_ptr->head == NULL) // empty list
        return -1;
    temp = list_ptr->head;
    list_ptr->head = temp->next;
    if (list_ptr->head == NULL) // only one element
        list_ptr->tail = NULL;
    val = temp->val;
    free(temp);
    return val;
} //remove node from front and return value

bool empty(struct list the_list) {
    return the_list.head == NULL;
} //returns true if list is empty

void delete(struct list *list_ptr) {
    struct node *temp = list_ptr->head;
    while (temp != NULL) {
        list_ptr->head = temp->next;
        free(temp);
        temp = list_ptr->head;
    }
    list_ptr->tail = NULL;
} //remove all nodes from list
