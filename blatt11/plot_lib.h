#ifndef PLOT_LIB_H
#define PLOT_LIB_H

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

void plot(Settings* settings, Function* functions, size_t num_functions);

#endif /* PLOT_LIB_H */
