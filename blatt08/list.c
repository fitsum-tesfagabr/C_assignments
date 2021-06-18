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
  if (n != NULL) {
    return n->next;
  }
  return NULL;
}

Node* node_prev(Node* n) {
  if (n != NULL) {
    return n->prev;
  }
  return NULL;
}
int* node_val(Node* n) {
  if (n != NULL) {
    return &n->val;
  }
  return NULL;
}
struct List {
  Node* first;
  Node* last;
  size_t len;
};

List* list_new(void) {
  List* list = malloc(sizeof(List));
  if (list == NULL) {
    exit(1);
  }
  list->first = NULL;
  list->last = NULL;
  list->len = 0;
  return list;
}

void list_free(List* l) {
  free(l->first);
  free(l->last);
  free(l);
}

Node* list_first(List* l) {
  if (l != NULL) {
    return l->first;
  }
  return NULL;
}
Node* list_last(List* l) {
  if (l != NULL) {
    return l->last;
  }
  return NULL;
}
size_t list_len(List* l) {
  if (l != NULL) {
    return l->len;
  }
  return -1;
}

void list_push_back(List* l, int val) {
  if (l != NULL) {
    Node* n = malloc(sizeof(Node));
    if (n == NULL) {
      exit(1);
    }
    n->val = val;
    n->prev = list_last(l);
    n->next = NULL;
    /* Check first if list is empty */
    if (l->len == 0) {
      l->first = n;
      l->last = n;
      l->len += 1;
    } else {

      l->last->next = n;
      l->last = n;

      l->len += 1;
    }
  }
}

void list_push_front(List* l, int val) {
  if (l != NULL) {
    Node* n = malloc(sizeof(Node));
    if (n == NULL) {
      exit(1);
    }
    n->val = val;
    n->prev = NULL;
    n->next = list_first(l);
    /* Check first if list is empty */
    if (l->len == 0) {
      l->first = n;
      l->last = n;
      l->len += 1;
    } else {
      l->first->prev = n;
      l->first = n;
      l->len += 1;
    }
  }
}

int list_pop_back(List* l) {
  if (l != NULL) {
    Node* n = l->last;
    /* Check first if list is empty */
    if (l->len == 0) {
      exit(1);
    } else if (l->len == 1) {
      int x = list_last(l)->val;
      l->last = l->last->prev;
      l->first = NULL;
      l->len -= 1;
      free(n);
      return x;
    } else {
      int x = list_last(l)->val;
      l->last = list_last(l)->prev;
      l->last->next = NULL;
      l->len -= 1;
      free(n);
      return x;
    }
  }
  exit(1);
}

int list_pop_front(List* l) {
  if (l != NULL) {
    Node* n = l->first;
    /* Check first if list is empty */
    if (l->len == 0) {
      exit(1);
    } else if (l->len == 1) {
      int x = list_first(l)->val;
      l->first = list_first(l)->next;
      l->last = NULL;
      l->len -= 1;
      free(n);
      return x;
    } else {
      int x = list_first(l)->val;
      l->first = list_first(l)->next;
      l->first->prev = NULL;
      l->len -= 1;
      free(n);
      return x;
    }
  }
  exit(1);
}
