#include "./tui.h"
#include "./ansi_codes.h"

/* The following global variables are declared to be `static`. This makes the
 * variables local to this `.c`-file, such that it is still ok to use
 * those variable names for global variables in other `.c`-files.
 * This is all that `static` does, so you can basically ignore that it's there.
 */

/* How the terminal currently looks like. */
static Matrix* old = NULL;

/* How the terminal should look like after the next update. */
static Matrix* new = NULL;

/* Cell used to initialize new terminal cells, e.g. at the beginning or after
 * the terminal was resized.
 */
static Cell def_cell = (Cell){
    .content = ' ', .text_color = FG_WHITE, .background_color = BG_BLACK};

/* Cell which is different from all regular cells.
 *
 * If `old` contains a `null_cell`, then the next call to `tui_update` will
 * definitely redraw the cell from `new` at the same position.
 */
static Cell null_cell =
    (Cell){.content = 0, .text_color = "", .background_color = ""};

void tui_init(void) {
  set_raw_terminal_mode();

  printf("%s", CURSOR_HIDE);
  printf("%s", CLEAR_SCREEN);

  Size2 size = query_size();
  new = matrix_new(size.x, size.y, &def_cell);
  old = matrix_new(size.x, size.y, &null_cell);
}

void tui_shutdown(void) {
  matrix_free(new);
  matrix_free(old);

  printf("%s", COLOR_RESET);
  printf("%s", CURSOR_SHOW);
  printf("%s", CLEAR_SCREEN);
  move_cursor_to(0, 0);

  fflush(stdout);
}

Cell* tui_cell_at(size_t x, size_t y) {
  return matrix_cell_at(new, x, y);
}

void tui_set_str_at(size_t x, size_t y, const char* s, const char* text_color,
                    const char* background_color) {
  matrix_set_str_at(new, x, y, s, text_color, background_color);
}

Size2 tui_size(void) {
  Size2 size = query_size();
  if (size.x != matrix_width(new) || size.y != matrix_height(new)) {
    matrix_free(old);
    old = matrix_new(size.x, size.y, &null_cell);
    matrix_resize(new, size.x, size.y, &def_cell);
  }
  return size;
}

void tui_update(void) {
  matrix_print_update(old, new);
}

void tui_clear_with(Cell* c) {
  matrix_clear_with(new, c);
}

void tui_clear(void) {
  matrix_clear(new);
}
