#include "./ansi_codes.h"
#include <stdio.h>

int main(void) {
  printf(CLEAR_SCREEN);

  for (int i = 0; i < 3; i++) {
    move_cursor_to(i, 0);
    for (int j = 0; j < 20; j++) {
      printf("#");
    }
    fflush(stdout);
  }

  move_cursor_to(1, 5);
  printf(FG_RED "hello" COLOR_RESET);
  fflush(stdout);
  move_cursor_to(4, 0);
  return 0;
}
