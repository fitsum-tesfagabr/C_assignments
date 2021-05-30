#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./vec.h"

struct Vec {
  int *data;       /* dynamic memory area containing the integers */
  size_t length;   /* how many integers are currently stored in data */
  size_t capacity; /* how many integers can be stored in data */
};

Vec *vec_new() {

  Vec *new_vec = malloc(sizeof(Vec));
  new_vec->length = 0;
  new_vec->capacity = 1;
  new_vec->data = malloc(new_vec->capacity * sizeof(int));
  return new_vec;
}

void vec_free(Vec *xs) {
  if (xs != NULL) {
    free(xs->data);
    free(xs);
  }
}

int *vec_at(Vec *xs, size_t i) {
  if (xs == NULL) {
    return NULL;
  }
  /* i must be in the range, if not NULL pointer will be returned*/
  if (i < xs->length && i >= 0) {
    return (xs->data + i);
  }

  return NULL;
}

size_t vec_length(Vec *xs) {
  if (xs != NULL) {
    return xs->length;
  }
  return -1; /*xs does not refer to any memory*/
}

size_t vec_capacity(Vec *xs) {
  if (xs != NULL) {
    return xs->capacity;
  }
  return -1; /*xs does not refer to any memory*/
}

bool vec_push(Vec *xs, int x) {
  if (xs == NULL) {
    return false;
  }
  /* if there exist enough capacity, the element will be added
   * with out to increase the capacity, else the capacity will
   * be doubled
   */
  if (vec_length(xs) < vec_capacity(xs)) {
    xs->data[xs->length] = x;
    xs->length++; /* increase No. elements after pushing */
    return true;
  } else {
    xs->capacity *= 2;
    xs->data = realloc(xs->data, vec_capacity(xs) * sizeof(int));
    xs->data[xs->length] = x;
    xs->length++;
    return true;
  }
  return false;
}

void vec_pop(Vec *xs) {

  if (xs != NULL) {
    /* to pop elements there must be elements included */
    if (vec_length(xs) > 0) {
      xs->length--;
      /*After popping the capacity will be resized to half, if
       * the remaining elements can be stored in half of the
       * capacity.
       */
      if (xs->length == vec_capacity(xs) / 2 && vec_length(xs) != 0) {
        xs->capacity = vec_capacity(xs) / 2;
        xs->data = realloc(xs->data, vec_capacity(xs) * sizeof(int));
      }
    }
  }
}

void swap_int(int *x, int *y) {
  int temp;
  temp = *x;
  *x = *y;
  *y = temp;
}

int *vec_min_between(Vec *xs, size_t from, size_t to) {
  if (xs == NULL) {
    return NULL;
  }
  /* Normally range is expected to be from left to right and must be >= 0 */
  if (from < to && from >= 0) {
    /* the right index must be in range*/
    if (to > vec_length(xs)) {
      return NULL;
    }

    /* returns true if an element is compared with all the values
     * and is less than all the elements
     */
    bool complete = false;

    size_t min_location = from; /* index of smallest element */

    for (int i = from; i < to - 1; i++) {

      for (int j = i + 1; j < to; j++) {
        /* if the i'th element is greater than the next
         * element in the array, it need not be compared
         * with other elements. Therefore, the loop will
         * be break and the 'i + 1' will be checked again.*/
        if (xs->data[i] > xs->data[j]) {
          min_location = j; /* j'th element is smaller than i'th element */
          break;
        }
        /* after the element is compared with all the remaining
         * elements in the range and is smaller than all the
         * elements, no other operations are needed.
         * Therefore, the function terminates. */
        if (j == (to - 1)) {
          complete = true;
        }

      } // end of internal for loop
      if (complete) {
        break;
      }
    } // end of external for loop
    /* Location of the minimum element will be returned */
    return xs->data + min_location;
  }
  /* if 'from' is greater than 'to' it is confusing, therefore,
   * return NULL*/
  return NULL;
}

void vec_sort(Vec *xs) {
  /* if xs is NULL the function terminates automatically. */
  if (xs != NULL) {
    /* Starting by index 0, the minimum element will be evaluated and swapped
     * with the left most index. The left index will then be shifted to the
     * right after every iteration.
     */
    for (int i = 0; i < (vec_length(xs) - 1); i++) {
      swap_int(xs->data + i, vec_min_between(xs, i, vec_length(xs)));
    }
  }
}

/* prints the content of the vector xs */
void vec_print(Vec *xs) {
  if (xs != NULL) {
    // vec_sort(xs);
    printf("\nVector at address %p has %ld elements and capacity %ld.\n", xs,
           xs->length, xs->capacity);
    for (int i = 0; i < vec_length(xs); i++) {
      printf("  vec[%d] = %d (address %p)\n", i, xs->data[i], xs->data + i);
    }
  }
}
