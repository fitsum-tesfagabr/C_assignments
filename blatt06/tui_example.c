#include "./tui.h"
#include <unistd.h>
int main(void) {
  tui_init();

  char c = '!';
  int t = 0;

  while (1) {
    if (stdin_has_changed()) {
      c = read_from_stdin();
      if (c == 'q')
        break;
    }

    Size2 size = tui_size();

    tui_clear();

    Cell* cell = tui_cell_at(1 + ((t + size.x - 2) % (size.x)), size.y / 2);
    cell->content = c;
    cell->text_color = FG_RED;
    cell->background_color = BG_WHITE;
    Cell* cell1 =
        tui_cell_at(1 + ((t + size.x - 1) % (size.x)), 1 + size.y / 2);
    cell1->content = c;
    cell1->text_color = FG_YELLOW;
    cell1->background_color = BG_WHITE;

    cell = tui_cell_at(1 + ((t + size.x) % (size.x)), 2 + size.y / 2);
    cell->content = c;
    cell->text_color = FG_CYAN;
    cell->background_color = BG_WHITE;

    tui_update();

    t += 1;

    usleep(1000000);
  }

  tui_shutdown();

  return 0;
}
