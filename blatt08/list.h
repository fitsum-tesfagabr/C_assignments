#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stddef.h>

/* A doubly linked list. */
typedef struct List List;

/* A node of a doubly-linked list. */
typedef struct Node Node;

/* Create an empty list. */
List* list_new(void);

/* Free the list and its nodes. */
void list_free(List* l);

/* Returns the first node of the list, if it exists, otherwise `NULL`. */
Node* list_first(List* l);

/* Returns the last node of the list, if it exists, otherwise `NULL`. */
Node* list_last(List* l);

/* Returns the length of the list. */
size_t list_len(List* l);

/* Append an element `val` at the front of list `l`. */
void list_push_front(List* l, int val);

/* Append an element `val` at the back of list `l`. */
void list_push_back(List* l, int val);

/* Remove an element at the front of list `l` and return it. */
int list_pop_front(List* l);

/* Remove an element at the back of list `l` and return it. */
int list_pop_back(List* l);

/* Returns the node after `n`, if it exists, otherwise `NULL`. */
Node* node_next(Node* n);

/* Returns the node before `n`, if it exists, otherwise `NULL`. */
Node* node_prev(Node* n);

/* Return a pointer to the int value stored in node `n`. */
int* node_val(Node* n);

#endif /* LIST_H */
