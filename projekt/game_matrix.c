#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./game_matrix.h"

struct GameMatrix {
  Cell* cells;
  size_t width;
  size_t height;
};

GameMatrix* game_matrix_new(size_t width, size_t height, Cell* def) {
  GameMatrix* m = malloc(sizeof(GameMatrix));
  if (m == NULL) {
    return NULL;
  }

  *m = (GameMatrix){.cells = malloc(width * height * sizeof(Cell)),
                    .height = height,
                    .width = width};

  if (m->cells == NULL) {
    free(m);
    return NULL;
  }

  for (size_t i = 0; i < width * height; i++) {
    m->cells[i] = *def;
  }

  return m;
}

void game_matrix_free(GameMatrix* m) {
  free(m->cells);
  free(m);
}

size_t game_matrix_width(GameMatrix* m) {
  return m->width;
}

size_t game_matrix_height(GameMatrix* m) {
  return m->height;
}

Cell* game_matrix_at(GameMatrix* m, size_t x, size_t y) {
  assert(x < m->width);
  assert(y < m->height);
  return m->cells + y * m->width + x;
}
