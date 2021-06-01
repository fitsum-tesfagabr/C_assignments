#include <unistd.h>

#include "./tui.h"

int main(void) {
  tui_init();

  char c = '!';
  size_t t = 0;

  while (1) {
    if (stdin_has_changed()) {
      c = read_from_stdin();
      if (c == 'q')
        break;
    }

    Size2 size = tui_size();

    tui_clear();

    Cell* cell = tui_cell_at(size.x / 2 + (t % 3), size.y / 2);
    cell->content = c;
    cell->text_color = FG_RED;
    cell->background_color = BG_BLACK;

    tui_update();

    t += 1;

    usleep(100000);
  }

  tui_shutdown();

  return 0;
}
