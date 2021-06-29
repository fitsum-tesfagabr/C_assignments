#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <math.h>

#include "./game_of_life_lib.h"

bool handle_input(GameState* gs, char c) {
  if (c == 'q') {
    return true;
  }
  return false;
}

void update(GameState* gs) {
}

void draw(GameState* gs) {
}
