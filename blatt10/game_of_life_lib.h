#ifndef GAME_OF_LIFE_LIB_H
#define GAME_OF_LIFE_LIB_H

#include "../tui/tui.h"
#include "./bool_matrix.h"
#include <stddef.h>
#include <stdlib.h>

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

/* Prove if points are inside the field_size.
 * Return 'True' if the points are inside field,
 * otherwise return 'False'
 */
bool inside_boundry(GameState* gs, int x, int y);

/* Control the key pressed by user and take appropriate
 * action for each key.
 */
bool handle_input(GameState* gs, char c);
/* Update field with new state */
void update(GameState* gs);
/* Draw each cell value for the future state */
void draw(GameState* gs);
/* Print cells based on their state.
 * If state of cell is true, '#' will be printed on the cells
 * else ' '.
 * */
void print_cells(GameState* gs);
/* print one cell */
void print_cell(GameState* gs, Size2 size, const char c);
/* Draws the cursor position by setting the background to white. */
void print_cursor(GameState* gs, Size2 size);
/* Compares cell status.
 * Return 'True' if the cells state is same, else 'False'. */
bool cells_eq(BoolMatrix* c1, BoolMatrix* c2, int x, int y);
/* count the number of live neighbour and returns the total
 * live neighbouring cells
 */
int count_live_cells(GameState* gs, int x, int y);
/* When key 'u' or 'o' or 'i' is pressed the current field will be saved to
 * save_u.gol, save_o.gol and save_i.gol respectively. */
void write_to_file(GameState* gs, FILE* file);
/* When key 'U' or 'O' or 'I' is pressed, data from the files save_u.gol,
 * save_o.gol, and save_i.gol respectively will be read if they exist.
 * if the files does not exist the keys will be ignored
 **/
void read_from_file(GameState* gs, FILE* file);

#endif /* GAME_OF_LIFE_LIB_H */
