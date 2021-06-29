#ifndef GAME_OF_LIFE_LIB_H
#define GAME_OF_LIFE_LIB_H

#include <stddef.h>
#include "../tui/tui.h"
#include "./bool_matrix.h"

typedef struct GameState {
  size_t time_step;
  size_t speed;
  bool simulation_active;
  bool selection_active;
  Size2 selection_start;
  Size2 cursor_pos;
  Size2 field_size;
  BoolMatrix* m_cur;
  BoolMatrix* m_next;
} GameState;

bool handle_input(GameState* gs, char c);

void update(GameState* gs);

void draw(GameState* gs);

#endif /* GAME_OF_LIFE_LIB_H */
