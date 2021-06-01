#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "./ansi_codes.h"
#include "./tui_matrix.h"

/* Representation of the terminal content as a matrix of `cells` for a terminal
 * which is large enough to display `width` x `height` characters.
 */
struct Matrix {
  Cell* cells;
  size_t width;
  size_t height;
};

Cell* matrix_cell_at(Matrix* m, size_t x, size_t y) {
  /* TODO */
}

Matrix* matrix_new(size_t width, size_t height, Cell* def) {
  /* TODO */
}

void matrix_free(Matrix* m) {
  /* TODO */
}

size_t matrix_width(Matrix* m) {
  /* TODO */
}

size_t matrix_height(Matrix* m) {
  /* TODO */
}

void matrix_clear_with(Matrix* m, Cell* c) {
  /* TODO */
}

void matrix_clear(Matrix* m) {
  /* TODO */
}

void matrix_resize(Matrix* m, size_t width, size_t height, Cell* def) {
  /* TODO */
}

/* You might want to define this function:
bool cell_eq(Cell* c1, Cell* c2) {
}
*/

void matrix_print_update(Matrix* old, Matrix* new) {
  /* TODO */
}

void matrix_set_str_at(Matrix* m, size_t x, size_t y, const char* s,
                       const char* text_color, const char* background_color) {
  /* TODO */
}
