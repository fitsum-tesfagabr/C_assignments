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

/* Define all the properties needed for the game inside a structure */
typedef enum PlayMode { PLAY, MENU, PAUSE } PlayMode;

typedef struct Int2 {
  size_t x;
  size_t y;
} Int2;

typedef struct Highscore {
  int points;
  int width;
  int height;
  double probability;
  int play_time;
} H_score;

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
void exit_safely(GameState* gs);
void draw_info_bar(GameState* gs);
void draw_frame(GameState* gs);
void draw_cursor(GameState* gs);
void draw_new_game(GameState* gs);
void draw_default(GameState* gs);
void create_new_game(GameState* gs);
void update_cells_status(GameState* gs);
int count_mines(GameState* gs, int x, int y, char c);
void open_safe_cells(GameState* gs, int x, int y);
void free_safe_cells(GameState* gs, int x, int y, GameMatrix* m);
char cell_content(GameMatrix* m, int x, int y);
void copy_content(GameState* gs, GameMatrix* dest, GameMatrix* source);
bool is_all_visited(GameState* gs);
int count_safe_cells(GameState* gs);
bool is_winner(GameState* gs);
bool handle_input(GameState* gs, char c);
void reset_game(GameState* gs, Vec* vector);
char* fgetline(FILE* file);
void read_settings(GameState* gs, FILE* file);
void write_settings(GameState* gs, FILE* file);
#endif
