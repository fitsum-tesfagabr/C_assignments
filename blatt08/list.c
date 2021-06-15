#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./list.h"

struct Node {
  int val;
  Node* prev;
  Node* next;
};

Node* node_next(Node* n) {
}
Node* node_prev(Node* n) {
}
int* node_val(Node* n) {
}

struct List {
  Node* first;
  Node* last;
  size_t len;
};

List* list_new(void) {
}

void list_free(List* l) {
}

Node* list_first(List* l) {
}
Node* list_last(List* l) {
}
size_t list_len(List* l) {
}

void list_push_back(List* l, int val) {
}

void list_push_front(List* l, int val) {
}

int list_pop_back(List* l) {
}

int list_pop_front(List* l) {
}
