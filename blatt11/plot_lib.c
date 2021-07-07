#include "./plot_lib.h"
#include "../tui/tui.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

bool handle_input(GameState* gs, char c) {
  if (c == 'q') {
    return true;
  } else if (c == '+') {
    gs->zoom++;
  } else if (c == '-') {
    if (gs->zoom > 2) {
      gs->zoom--;
    }
  }
  return false;
}

void plot(GameState* gs, Settings* settings, Function* functions,
          size_t num_functions) {
  double y;

  for (int i = 0; i < num_functions; i++) {
    Function func = functions[i];

    for (int i = 0; i < settings->x_max; i++) {
      /* The functions oscillate around half of the screen */
      y = settings->y_max / 2 +
          (gs->zoom) *
              func.f((double)i / (gs->zoom + 3), (double)gs->time_steps / 15);
      /* The pionts inside the screen will be displayed */
      if (y >= settings->y_min && y < settings->y_max) {
        Cell* cell = tui_cell_at(i, y);
        cell->content = '#';
        cell->text_color = func.fg_color;
        cell->background_color = func.bg_color;
      } // end of if
    }   // end of internal for loop
  }     // end of external for loop
} // end of function plot
