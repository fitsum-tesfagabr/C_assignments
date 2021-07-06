#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./ivec.h"

struct IntVec {
  int* data;       /* dynamic memory area containing the integers */
  size_t length;   /* how many integers are currently stored in data */
  size_t capacity; /* how many integers can be stored in data */
};

IntVec* ivec_new() {
  IntVec* xs = malloc(sizeof(IntVec));
  if (xs == NULL) {
    return NULL;
  }
  xs->capacity = 1;
  xs->length = 0;
  xs->data = malloc(xs->capacity * sizeof(int));
  if (xs->data == NULL) {
    return NULL;
  }
  return xs;
}

void ivec_free(IntVec* xs) {
  free(xs->data);
  free(xs);
}

int* ivec_at(IntVec* xs, size_t i) {
  return xs->data + i;
}

size_t ivec_length(IntVec* xs) {
  return xs->length;
}

size_t ivec_capacity(IntVec* xs) {
  return xs->capacity;
}

bool ivec_set_capacity(IntVec* xs, size_t capacity) {
  if (xs->length <= capacity) {
    xs->capacity = capacity;
    xs->data = realloc(xs->data, capacity * sizeof(int));
    return xs->data != NULL;
  }
  return true;
}

bool ivec_push(IntVec* xs, int x) {
  if (xs->capacity == xs->length) {
    bool success = ivec_set_capacity(xs, xs->capacity * 2);
    if (!success) {
      return false;
    }
  }
  xs->data[xs->length] = x;
  xs->length++;
  return true;
};

int ivec_pop(IntVec* xs) {
  xs->length--;
  int x = *ivec_at(xs, xs->length - 1);
  if (xs->length * 2 == xs->capacity) {
    ivec_set_capacity(xs, xs->length);
  }
  return x;
}

int ivec_remove(IntVec* xs, size_t i) {
  xs->length--;
  int x = *ivec_at(xs, i);
  for (size_t j = i; j < xs->length; ++j) {
    *ivec_at(xs, j) = *ivec_at(xs, j + 1);
  }
  return x;
}

void ivec_print(IntVec* xs) {
  printf("IntVector at address %p has %ld elements and capacity %ld.\n", xs,
         ivec_length(xs), ivec_capacity(xs));
  for (size_t i = 0; i < ivec_length(xs); ++i) {
    int* xi = ivec_at(xs, i);
    printf("  vec[%ld] = %d (address %p)\n", i, *xi, xi);
  }
  printf("\n");
}
