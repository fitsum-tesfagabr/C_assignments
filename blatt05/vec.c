#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./vec.h"

struct Vec {
  int* data;       /* dynamic memory area containing the integers */
  size_t length;   /* how many integers are currently stored in data */
  size_t capacity; /* how many integers can be stored in data */
};

/*

Vec *vec_new() {
}

void vec_free(Vec *xs) {
}

int *vec_at(Vec *xs, size_t i) {
}

size_t vec_length(Vec *xs) {
}

size_t vec_capacity(Vec *xs) {
}

bool vec_push(Vec *xs, int x) {
};

void vec_pop(Vec *xs) {
}

void swap_int(int *x, int *y) {
}

int *vec_min_between(Vec *xs, size_t from, size_t to) {
}

void vec_sort(Vec *xs) {
}

void vec_print(Vec *xs) {
}

*/
