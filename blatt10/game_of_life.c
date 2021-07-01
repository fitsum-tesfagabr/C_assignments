#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "../tui/tui.h"
#include "./bool_matrix.h"
#include "./game_of_life_lib.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int main(int argc, char** argv) {
  if (argc != 3) {
    printf("USAGE\n");
    printf("  %s WIDTH HEIGHT\n", argv[0]);
    exit(1);
  }
  size_t width;
  size_t height;
  if (sscanf(argv[1], "%ld", &width) != 1) {
    printf("ERROR: Failed to read width from args.\n");
    exit(1);
  }
  if (sscanf(argv[2], "%ld", &height) != 1) {
    printf("ERROR: Failed to read height from args.\n");
    exit(1);
  }

  tui_init();

  GameState gs = (GameState){
      .time_step = 0,
      .speed = 25,
      .simulation_active = false,
      .selection_active = false,
      .cursor_pos = {0, 0},
      .m_cur = bool_matrix_new(width, height, false),
      .m_next = bool_matrix_new(width, height, false),
  };
  while (1) {
    Size2 size = tui_size();

    gs.field_size = (Size2){MIN(bool_matrix_width(gs.m_cur), size.x),
                            MIN(bool_matrix_height(gs.m_cur), size.y)};

    if (stdin_has_changed()) {
      char c = read_from_stdin();
      if (handle_input(&gs, c)) {
        break;
      }
    }

    update(&gs);

    tui_clear();

    draw(&gs);

    tui_update();

    gs.time_step += 1;

    usleep(10000);
  }

  bool_matrix_free(gs.m_cur);
  bool_matrix_free(gs.m_next);

  tui_shutdown();

  return 0;
}
