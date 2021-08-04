#ifndef MINI_SWEEPER_LIB_H
#define MINI_SWEEPER_LIB_H
#include "./game_matrix.h"
#include "./vec.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "./json_data.h"
#include "./json_printer.h"
#include "./json_reader.h"
#include "./memtools.h"
#include "./mini_sweeper_lib.h"
#include "./reader.h"
#include "./vec.h"

/* Define all the MODES needed for the game inside a structure */
typedef enum PlayMode { PLAY, MENU, PAUSE } PlayMode;

/* Datastructure for coordinates */
typedef struct Int2 {
  size_t x;
  size_t y;
} Int2;

/* Datastructure for Score infor */
typedef struct Highscore {
  int points;
  int width;
  int height;
  double probability;
  int play_time;
} H_score;

/* Game Properties */
typedef struct GameState {
  Size2 term_size;
  Int2 field_begin;
  Int2 field_end;
  Int2 field_size;
  Int2 play_field_begin;
  Int2 play_field_end;
  Int2 cursor_pos;
  PlayMode mode;
  Vec* highscores;
  time_t start_time;
  char* endgame_info;
  size_t play_field_width;
  size_t play_field_height;
  size_t points;
  int time_step;
  int play_time;
  float probability;
  int count_flags;
  GameMatrix* game_field;
  GameMatrix* new_game;
  Vec* mines;
  Vec* flags;
  Vec* no_mines;
  bool explosion;

} GameState;

/* Clean pre defined properties and exit safely with out memory leaks and
 * Terminal will be set to its default */
void exit_safely(GameState* gs);

/* Display necessary infos while playing. Ex. play time in seconds */
void draw_info_bar(GameState* gs);

/* Display Mine sweeper frame */
void draw_frame(GameState* gs);

/* Display Cursor around the field */
void draw_cursor(GameState* gs);

/* Display Game patterns */
void draw_new_game(GameState* gs);

/* Fill all play field cells with '.' */
void draw_default(GameState* gs);

/* Generate new game. Random mines are shuffled and distributed around the
 * block. */
void create_new_game(GameState* gs);
void update_cells_status(GameState* gs);

/* Count neighbouring 8 cells with mines. */
int count_mines(GameState* gs, int x, int y, char c);

/* If Cell with no-neighouring cells with mines are pressed then the
 * neighbouring cells with no mines will be opened */
void open_safe_cells(GameState* gs, int x, int y);
void free_safe_cells(GameState* gs, int x, int y, GameMatrix* m);

/* Retruns either '.', '*', ' ' or a number. */
char cell_content(GameMatrix* m, int x, int y);

/* Copy one cell info to another cell info */
void copy_content(GameState* gs, GameMatrix* dest, GameMatrix* source);

/* Check if Player has opened all cells or set flag on Cells*/
bool is_all_visited(GameState* gs);

/* Count cells with no mines */
int count_safe_cells(GameState* gs);

/* Check for Winning */
bool is_winner(GameState* gs);

/* Manage input keys by user */
bool handle_input(GameState* gs, char c);

/* Set every cell to default */
void reset_game(GameState* gs, Vec* vector);

/* Read setting infos from file */
void read_settings(GameState* gs, FILE* file);

/* Write setting infos to file */
void write_settings(GameState* gs, FILE* file);
#endif
