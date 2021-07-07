#ifndef PLOT_LIB_H
#define PLOT_LIB_H
#include <stdbool.h>
#include <stddef.h>
typedef struct Function {
  double (*f)(double, double);
  char* fg_color;
  char* bg_color;
} Function;

typedef struct Settings {
  double x_min;
  double x_max;
  double y_min;
  double y_max;
} Settings;

typedef struct GameState {
  size_t time_steps;
  size_t zoom;
} GameState;

bool handle_input(GameState* gs, char c);

void plot(GameState* gs, Settings* settings, Function* functions,
          size_t num_functions);

#endif /* PLOT_LIB_H */
