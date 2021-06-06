#include <stdio.h>
#include <stdlib.h>

#include "./ansi_codes.h"
#include "./tui_matrix.h"

int main(void) {
  Cell def_cell = (Cell){
      .content = '.', .text_color = FG_WHITE, .background_color = BG_BLACK};

  Matrix* old = matrix_new(10, 10, &def_cell);
  Matrix* new = matrix_new(10, 10, &def_cell);

  /* TEST 1: Should show ten empty lines, because old and new are equal.
   * The cursor should be visible at row 10 column 10.
   */
  printf(CLEAR_SCREEN);
  matrix_print_update(old, new);

  /* Wait for the user to press enter, so we have time to look at the terminal.
   */
  getchar();

  /* TEST 2: Should print only the three characters with the corresponding
   * colors and at the corresponding rows and columns.
   * The cursor should be visible at row 10 column 10.
   */
  matrix_cell_at(new, 3, 5)->content = 'f';
  matrix_cell_at(new, 3, 5)->text_color = FG_RED;
  matrix_cell_at(new, 3, 5)->background_color = BG_WHITE;

  matrix_cell_at(new, 5, 5)->content = 'o';
  matrix_cell_at(new, 5, 5)->text_color = FG_GREEN;
  matrix_cell_at(new, 5, 5)->background_color = BG_WHITE;

  matrix_cell_at(new, 7, 5)->content = 'o';
  matrix_cell_at(new, 7, 5)->text_color = FG_BLUE;
  matrix_cell_at(new, 7, 5)->background_color = BG_WHITE;

  matrix_print_update(old, new);

  /* Wait for the user to press enter, so we have time to look at the terminal.
   */
  getchar();

  /* TEST 3: Should print nothing new, because old and new are equal. */
  matrix_print_update(old, new);

  /* Wait for the user to press enter, so we have time to look at the terminal.
   */
  getchar();

  matrix_free(new);
  matrix_free(old);

  return 0;
}
