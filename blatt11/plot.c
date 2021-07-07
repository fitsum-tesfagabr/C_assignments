#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <math.h>

#include "../tui/tui.h"
#include "./plot_lib.h"

double moving_sin(double x, double t){
        return sin(x - t);
}
double moving_cos(double x, double t){
        return cos(x - t);
}
double moving_weird(double x, double t){
        return sin(x - t * 2)*tan(x - t*3);
}
double moving_weird2(double x, double t){
        return sin(x - t*2)*sin(x*x - t*3);
}

int main(void) {
  tui_init();

  Function fuctions[] = {
        { .f = moving_sin, .fg_color = FG_RED, .bg_color = BG_BLACK},
        { .f = moving_cos, .fg_color = FG_YELLOW, .bg_color = BG_BLACK},
        { .f = moving_weird, .fg_color = FG_MAGENTA, .bg_color = BG_BLACK},
        { .f = moving_weird2, .fg_color = FG_GREEN, .bg_color = BG_BLACK},
  };
  Settings settings = {
        .x_min = 0.0,
        .y_min = 0.0,
        .x_max = tui_size().x,
        .y_max = tui_size().y
  };
  GameState gs = {
        .time_steps = 0,
        .zoom = 6
  };
  while(1){
        settings.x_max = tui_size().x;
        settings.y_max = tui_size().y;

        if(stdin_has_changed()){
            char c = read_from_stdin();
            if(handle_input(&gs, c))
              break;
        }
        
        tui_clear();
        
        plot(&gs, &settings, fuctions, 4);
        
        tui_update();
        gs.time_steps++;
        usleep(5000);
  }
  tui_shutdown();
  return 0;
}
