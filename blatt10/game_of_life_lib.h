#ifndef GAME_OF_LIFE_LIB_H
#define GAME_OF_LIFE_LIB_H

#include "../tui/tui.h"
#include "./bool_matrix.h"
#include <stddef.h>

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

bool inside_boundry(GameState* gs, int x, int y);

void cursor(GameState* gs, Size2 size, const char c);

bool handle_input(GameState* gs, char c);

void update(GameState* gs);

void draw(GameState* gs);

void change_state(GameState* gs);

void print_cell(GameState* gs, Size2 size, const char c);

void print_cursor(GameState* gs, Size2 size);

bool cells_eq(BoolMatrix* c1, BoolMatrix* c2, int x, int y);

int count_live_cells(GameState* gs, int x, int y);

void write_to_file(GameState* gs, FILE* file);

void read_from_file(GameState* gs, FILE* file);
#endif /* GAME_OF_LIFE_LIB_H */
