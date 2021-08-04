#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./vec.h"
#include "./mini_sweeper_lib.h"

struct Vec {
  void** data;     /* dynamic memory area containing the integers */
  size_t length;   /* how many integers are currently stored in data */
  size_t capacity; /* how many integers can be stored in data */
};

Vec* vec_new() {
  Vec* xs = malloc(sizeof(Vec));
  if (xs == NULL) {
    return NULL;
  }
  xs->capacity = 1;
  xs->length = 0;
  xs->data = malloc(xs->capacity * sizeof(void*));
  if (xs->data == NULL) {
    return NULL;
  }
  return xs;
}

void vec_free(Vec* xs) {
  while (vec_length(xs) > 0) {
    vec_pop(xs);
  }
  free(xs->data);
  free(xs);
}

void** vec_at(Vec* xs, size_t i) {
  return xs->data + i;
}

size_t vec_length(Vec* xs) {
  return xs->length;
}

size_t vec_capacity(Vec* xs) {
  return xs->capacity;
}

bool vec_set_capacity(Vec* xs, size_t capacity) {
  if (xs->length <= capacity) {
    xs->capacity = capacity;
    xs->data = realloc(xs->data, capacity * sizeof(void*));
    return xs->data != NULL;
  }
  return true;
}

bool vec_push(Vec* xs, void* x) {
  if (xs->capacity == xs->length) {
    bool success = vec_set_capacity(xs, xs->capacity * 2);
    if (!success) {
      return false;
    }
  }
  xs->data[xs->length] = x;
  xs->length++;
  return true;
};

void vec_pop(Vec* xs) {
  xs->length--;
  void* x = *vec_at(xs, xs->length);
  free(x);
  if (xs->length * 2 == xs->capacity) {
    vec_set_capacity(xs, xs->length);
  }
}

void vec_remove(Vec* xs, size_t i) {
  void* x = *vec_at(xs, i);
  free(x);

  xs->length--;
  for (size_t j = i; j < xs->length; ++j) {
    *vec_at(xs, j) = *vec_at(xs, j + 1);
  }
}

void swap_location(Vec* xs, int x, int y) {
  void* tmp;
  tmp = xs->data[x];
  xs->data[x] = xs->data[y];
  xs->data[y] = tmp;
}

int vec_max_between(Vec *xs, size_t from, size_t to) {
  if (xs == NULL) {
    return -1;
  }
  // Normally range is expected to be from left to right and must be >= 0 //
  if (from < to && from >= 0) {
    // the right index must be in range
    if (to > vec_length(xs)) {
      return -1;
    }

    // returns true if an element is compared with all the values
    // and is less than all the elements
    //
    bool complete = false;

    size_t max_location = from; // index of smallest element 

    for (int i = from; i < to - 1; i++) {

      for (int j = i + 1; j < to; j++) {
        // if the i'th element is greater than the next
        // element in the array, it need not be compared
        // with other elements. Therefore, the loop will
        // be break and the 'i + 1' will be checked again.
        if (((H_score* )xs->data[j])->points > ((H_score*)xs->data[i])->points) {
          max_location = j; // j'th element is smaller than i'th element 
          break;
        }
        // after the element is compared with all the remaining
        // elements in the range and is smaller than all the
        // elements, no other operations are needed.
        // Therefore, the function terminates. 
        if (j == (to - 1)) {
          complete = true;
        }

      } // end of internal for loop
      if (complete) {
        break;
      }
    } // end of external for loop
    // Location of the minimum element will be returned 
    return max_location;
  }
  // if 'from' is greater than 'to' it is confusing, therefore,
  // return NULL
  return -1;
}

void vec_sort(Vec *xs) {
  // if xs is NULL the function terminates automatically. 
  if (xs != NULL) {
    // Starting by index 0, the minimum element will be evaluated and swapped
    // with the left most index. The left index will then be shifted to the
    // right after every iteration.
    //
    for (int i = 0; i < (vec_length(xs) - 1); i++) {
      swap_location(xs, i, vec_max_between(xs, i, vec_length(xs)));
    }
  }
}


void vec_print(Vec* xs) {
  printf("Vector at address %p has %ld elements and capacity %ld.\n", xs,
         vec_length(xs), vec_capacity(xs));
  for (size_t i = 0; i < vec_length(xs); ++i) {
    void** xi = vec_at(xs, i);
    printf("  vec[%ld] = %p (address %p)\n", i, *xi, xi);
  }
  printf("\n");
}
