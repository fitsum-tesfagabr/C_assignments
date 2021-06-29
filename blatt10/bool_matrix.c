#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "./bool_matrix.h"

struct BoolMatrix {
  bool* cells;
  size_t width;
  size_t height;
};

BoolMatrix* bool_matrix_new(size_t width, size_t height, bool def) {
  BoolMatrix* m = malloc(sizeof(BoolMatrix));
  if (m == NULL) {
    return NULL;
  }

  *m = (BoolMatrix) {
    .cells = malloc(height * width * sizeof(bool)),
    .height = height,
    .width = width
  };

  if (m->cells == NULL) {
    free(m);
    return NULL;
  }

  for (size_t i = 0; i < width * height; ++i) {
    m->cells[i] = def;
  }

  return m;
}


void bool_matrix_free(BoolMatrix* m) {
  free(m->cells);
  free(m);
}

size_t bool_matrix_width(BoolMatrix* m) {
  return m->width;
}

size_t bool_matrix_height(BoolMatrix* m) {
  return m->height;
}

bool* bool_matrix_at(BoolMatrix* m, size_t x, size_t y) {
  assert(x < m->width);
  assert(y < m->height);
  return m->cells + y * m->width + x;
}
