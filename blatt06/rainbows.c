#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "./tui.h"

/* You might want to approach it with the following two functions:

const char* rainbow_color(size_t i) {
}

void draw_rainbow_string(size_t x, size_t y, const char* s) {
}

*/

int main(int argc, char** argv) {

  /* TODO */

  tui_init();

  size_t t = 0;

  while (1) {
    if (stdin_has_changed()) {
      char c = read_from_stdin();
      if (c == 'q')
        break;
    }

    Size2 size = tui_size();

    tui_clear();

    /* TODO */

    tui_update();

    t += 1;

    usleep(100000);
  }

  tui_shutdown();

  return 0;
}
