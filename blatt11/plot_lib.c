#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "../tui/tui.h"
#include "./plot_lib.h"

bool handle_input(GameState* gs, char c){
     if (c == 'q'){
        return true;
     }
     else if(c == '+'){
        gs->zoom++;
     }
     else if(c == '-'){
        if (gs->zoom > 2){
        gs->zoom--;
        }
     }
     return false;
}

void plot(GameState* gs, Settings* settings, Function* functions, size_t num_functions) {
  Function sine = functions[0];
  double y = 1;
  for(int i=0; i < settings->x_max; i++){
  y = settings->y_max/2  + (gs->zoom)*sine.f((double) i/(gs->zoom + 3),(double) gs->time_steps/15);
  Cell* cell = tui_cell_at(i, y);
  cell->content = '#';
  cell->text_color = sine.fg_color;
  cell->background_color = sine.bg_color;
  }
  
  Function cosine = functions[1];
  y = 1;
  for(int i=0; i < settings->x_max; i++){
  y = settings->y_max/2  + (gs->zoom)*cosine.f((double) i/(gs->zoom + 3), (double)gs->time_steps/20);
  Cell* cell1 = tui_cell_at(i, y);
  cell1->content = '#';
  cell1->text_color = cosine.fg_color;
  cell1->background_color = cosine.bg_color;
  }
  
  Function weird = functions[3];
  y = 1;
  for(int i=0; i < settings->x_max; i++){
  y = settings->y_max/2  + (gs->zoom)*weird.f((double) i/(gs->zoom + 5), (double)gs->time_steps/20);
  Cell* cell2 = tui_cell_at(i, y);
  cell2->content = '#';
  cell2->text_color = weird.fg_color;
  cell2->background_color = weird.bg_color;
  }
}
