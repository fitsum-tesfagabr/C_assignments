#include "./tui_matrix.h"
#include "./ansi_codes.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Representation of the terminal content as a matrix of `cells` for a terminal
 * which is large enough to display `width` x `height` characters.
 */
struct Matrix {
  Cell* cells;
  size_t width;
  size_t height;
};

size_t address_x_y; /* Cantors address */
size_t index_x_y;   /* Cantors address */
size_t max_size;    /* Maximum cells to be set */

Cell* matrix_cell_at(Matrix* m, size_t x, size_t y) {
  /* Since Cantor index starts from 0, but rows and columns start
   * indexing from 1. It is necessary to deduct the values by 1.
   * It uses same principle like arrays
   * */
  assert(x > 0 && y > 0);
  assert(x <= matrix_width(m) && y <= matrix_height(m));

  x = x - 1;
  y = y - 1;
  /* Cantor index evaluation */
  address_x_y = ((x + y) * (x + y + 1)) / 2 + y;
  return (m->cells + address_x_y);
}

Matrix* matrix_new(size_t width, size_t height, Cell* def) {
  /* Allocate place in Memory for the new matrix */
  Matrix* m = malloc(sizeof(Matrix));
  assert(width > 0 && height > 0);
  if (m != NULL) {

    m->width = width;
    m->height = height;

    /* indexing starts form 0 */
    size_t x = width - 1;
    size_t y = height - 1;

    max_size = ((x + y) * (x + y + 1)) / 2 + y + 1; /* define max Nr. of Cells*/
    m->cells = malloc(max_size * sizeof(Cell));     /* reseve place for cells */

    if (m->cells != NULL) {

      for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
          /* Initialize each cell with the default value.
           * the indexing process follows the Cantor method for the whole
           * program
           */

          index_x_y = ((i + j) * (i + j + 1)) / 2 + j;
          (m->cells + index_x_y)->content = def->content;
          (m->cells + index_x_y)->text_color = def->text_color;
          (m->cells + index_x_y)->background_color = def->background_color;
        }
      }
      return m; /* Return Matrix */
    }
    return NULL; /* if m->cells is NULL*/
  }
  return NULL; /* if m is NULL */
}

void matrix_free(Matrix* m) {
  if (m != NULL) {
    free(m->cells);
    free(m);
    m = NULL;
  }
}

size_t matrix_width(Matrix* m) {
  return m->width;
}

size_t matrix_height(Matrix* m) {
  return m->height;
}

void matrix_clear_with(Matrix* m, Cell* c) {

  if (m != NULL && c != NULL) {
    for (int j = 0; j < matrix_height(m); j++) {
      for (int i = 0; i < matrix_width(m); i++) {

        index_x_y = ((i + j) * (i + j + 1)) / 2 + j; /* calculate cell index */
        (m->cells + index_x_y)->content = c->content;
        (m->cells + index_x_y)->text_color = c->text_color;
        (m->cells + index_x_y)->background_color = c->background_color;
      }
    }
  } // end of if
} // end of matrix_clear_with

void matrix_clear(Matrix* m) {
  if (m != NULL) {

    for (int j = 0; j < matrix_height(m); j++) {
      for (int i = 0; i < matrix_width(m); i++) {
        index_x_y = ((i + j) * (i + j + 1)) / 2 + j;
        (m->cells + index_x_y)->content = ' ';
        (m->cells + index_x_y)->text_color = FG_WHITE;
        (m->cells + index_x_y)->background_color = BG_BLACK;
      }
    }
  } // end of if
} // end of matrix_clear

void matrix_resize(Matrix* m, size_t width, size_t height, Cell* def) {
  /* there are six conditions which need to be considered before
   * resizing.
   */
  if (m != NULL && def != NULL) {
    assert(width > 0 && height > 0);

    if (matrix_width(m) >= width && matrix_height(m) >= height) {

      size_t x = width - 1;
      size_t y = height - 1;
      max_size = ((x + y) * (x + y + 1)) / 2 + y + 1;
      m->width = width;
      m->height = height;
      m->cells = realloc(m->cells, max_size * sizeof(Cell));
    }

    else if (matrix_width(m) >= width && matrix_height(m) < height) {
      size_t x = width - 1;
      size_t y = height - 1;
      size_t h_diff = height - matrix_height(m);

      m->width = width;
      m->height = height;

      max_size = ((x + y) * (x + y + 1)) / 2 + y + 1;
      m->cells = realloc(m->cells, max_size * sizeof(Cell));
      fill_matrix_height(m, h_diff, def);
    }

    else if (matrix_width(m) < width && matrix_height(m) >= height) {

      size_t x = width - 1;
      size_t y = height - 1;
      size_t w_diff = width - matrix_width(m);

      m->width = width;
      m->height = height;
      max_size = ((x + y) * (x + y + 1)) / 2 + y + 1;

      m->cells = realloc(m->cells, max_size * sizeof(Cell));
      fill_matrix_width(m, w_diff, def);
    }

    else {

      size_t x = width - 1;
      size_t y = height - 1;

      size_t h_diff = height - matrix_height(m);
      size_t w_diff = width - matrix_width(m);

      m->width = width;
      m->height = height;

      max_size = ((x + y) * (x + y + 1)) / 2 + y + 1;

      m->cells = realloc(m->cells, max_size * sizeof(Cell));
      fill_matrix_width(m, w_diff, def);
      fill_matrix_height(m, h_diff, def);
    }
  }
}

/* Fills only the newly created cells in the rows */
void fill_matrix_width(Matrix* m, size_t w_diff, Cell* def) {
  size_t start = matrix_width(m) - w_diff;
  size_t end = matrix_width(m);
  size_t h = matrix_height(m);

  for (int i = 0; i < h; i++) {
    for (int j = start; j < end; j++) {
      index_x_y = ((i + j) * (i + j + 1)) / 2 + i;
      (m->cells + index_x_y)->content = def->content;
      (m->cells + index_x_y)->text_color = def->text_color;
      (m->cells + index_x_y)->background_color = def->background_color;
    }
  }
}

/* Fills only the newly created cells in the columns */
void fill_matrix_height(Matrix* m, size_t h_diff, Cell* def) {

  size_t start = matrix_height(m) - h_diff;
  size_t end = matrix_height(m);

  for (int i = 0; i < matrix_width(m); i++) {
    for (int j = start; j < end; j++) {
      index_x_y = ((i + j) * (i + j + 1)) / 2 + j;
      (m->cells + index_x_y)->content = def->content;
      (m->cells + index_x_y)->text_color = def->text_color;
      (m->cells + index_x_y)->background_color = def->background_color;
    }
  }
}

bool cell_eq(Cell* c1, Cell* c2) {
  if (c1 != NULL && c2 != NULL) {
    if ((c1->content == c2->content) && (c1->text_color == c2->text_color) &&
        (c1->background_color == c2->background_color)) {
      return true;
    } else {
      return false;
    }
  }

  return false;
}

void matrix_print_update(Matrix* old, Matrix* new) {
  /* The cursor should stay hidden until the screen is updated.
   * Because it blinks and makes the screen disturbing.
   * It will be showed first when all the cells are updated.
   * */
  if (old != NULL && new != NULL) {

    printf(CURSOR_HIDE);
    for (int j = 0; j < matrix_height(new); j++) {
      for (int i = 0; i < matrix_width(new); i++) {

        index_x_y = ((i + j) * (i + j + 1)) / 2 + j;
        /* The cursor moves row by row after the current row is completed
         * updating
         */
        move_cursor_to(j, i);

        /* Cells are updated only when the new once are different. */
        if (!cell_eq(old->cells + index_x_y, new->cells + index_x_y)) {

          printf("%s%s%c", (new->cells + index_x_y)->text_color,
                 (new->cells + index_x_y)->background_color,
                 (new->cells + index_x_y)->content);
          /* After the cell is renewed the old Matrix will be updated with the
           * new once
           */
          (old->cells + index_x_y)->content = (new->cells + index_x_y)->content;
          (old->cells + index_x_y)->text_color =
              (new->cells + index_x_y)->text_color;
          (old->cells + index_x_y)->background_color =
              (new->cells + index_x_y)->background_color;
        } // end of if
      }   // end of for loop
    }     // end of for loop

    /* When all the cells are updated, the cursor will be moved to the
     * right-bottom edge
     */
    move_cursor_to(matrix_height(new) - 1, matrix_width(new) - 1);
    printf(CURSOR_SHOW);
    fflush(stdout);
  }
}

void matrix_set_str_at(Matrix* m, size_t x, size_t y, const char* s,
                       const char* text_color, const char* background_color) {
  size_t range = strlen(s);
  /* if the string does not fit on the screen, the range will be till the
   * end of the screen starting from x
   */
  if ((strlen(s) + x) > matrix_width(m)) {
    range = matrix_width(m) - x + 1;
  }

  /* If x and y are out of screen range, nothing happens */
  if (x <= matrix_width(m) && y <= matrix_height(m)) {
    size_t j;
    /* The cells will be updated step by step. */
    for (int i = 0; i < range; i++) {
      j = x + i;
      assert(s[i] != '\n');

      matrix_cell_at(m, j, y)->content = s[i];
      matrix_cell_at(m, j, y)->text_color = text_color;
      matrix_cell_at(m, j, y)->background_color = background_color;
    }
  }
}
