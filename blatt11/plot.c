#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "../tui/tui.h"
#include "./plot_lib.h"

double moving_sin(double x, double t) {
  return sin(x - t);
}
double moving_weird(double x, double t) {
  return sin(x - t * 2) * tan(x - t * 3);
}
double moving_weird2(double x, double t) {
  return sin(x * x - t) * cos(x - t);
}

double moving_weird3(double x, double t) {
  return sin(x - t)*sin(x - t) + cos(x*x - t)*cos(x*x - t);
}
int main(void) {
  tui_init();

  Function functions[] = {
      {.f = moving_sin, .fg_color = FG_HI_RED, .bg_color = BG_BLACK},
      {.f = moving_weird, .fg_color = FG_HI_CYAN, .bg_color = BG_BLACK},
      {.f = moving_weird2, .fg_color = FG_HI_BLUE, .bg_color = BG_BLACK},
      {.f = moving_weird3, .fg_color = FG_HI_YELLOW, .bg_color = BG_BLACK},
  };
  Settings settings = {
      .x_min = 0.0, .y_min = 0.0, .x_max = tui_size().x, .y_max = tui_size().y};
  GameState gs = {.time_steps = 0, .zoom = 7};
 
  size_t num_functions = sizeof(functions)/sizeof(functions[0]);
  while (1) {
    settings.x_max = tui_size().x;
    settings.y_max = tui_size().y;

    if (stdin_has_changed()) {
      char c = read_from_stdin();
      if (handle_input(&gs, c))
        break;
    }

    tui_clear();
    /* The number of fucntions can be changed basen on the supplied functions */
    plot(&gs, &settings, functions, num_functions);

    tui_update();
    gs.time_steps++;
    usleep(15000);
  }
  tui_shutdown();
  return 0;
}
