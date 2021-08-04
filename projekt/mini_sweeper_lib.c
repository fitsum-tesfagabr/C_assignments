#include "./mini_sweeper_lib.h"
#include "../tui/tui.h"
#include "./game_matrix.h"
#include "./menu.h"
#include "./vec.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

time_t get_time() {
  time_t now = time(0);
  return now;
}

void read_settings(GameState* gs, FILE* file) {
  char data[3][100];
  fgets(data[0], sizeof(data[0]), file);
  fgets(data[1], sizeof(data[1]), file);
  fgets(data[2], sizeof(data[2]), file);
  gs->play_field_width =
      atoi(data[0]) <= 50 && atoi(data[0]) >= 5 ? atoi(data[0]) : 15;
  gs->play_field_height =
      atoi(data[1]) <= 17 && atoi(data[1]) >= 5 ? atoi(data[1]) : 15;
  gs->probability =
      atof(data[2]) <= 1.0 && atof(data[2]) >= 0.01 ? atof(data[2]) : 0.15;
}

void write_settings(GameState* gs, FILE* file) {
  fprintf(file, "%ld\n", gs->play_field_width);
  fprintf(file, "%ld\n", gs->play_field_height);
  fprintf(file, "%.2f\n", gs->probability);
}

/*++++++++++++++++++++++++++++++++++++++++++++++++*/
void draw_frame(GameState* gs) {
  Cell c = (Cell){
      .content = ' ', .text_color = FG_WHITE, .background_color = BG_WHITE};
  Int2 frame_begin = {gs->field_begin.x, gs->field_begin.y};
  Int2 frame_end = {gs->field_begin.x + gs->play_field_width + 2,
                    gs->field_begin.y + gs->play_field_height + 2};
  for (size_t x = frame_begin.x; x < frame_end.x; ++x) {
    *tui_cell_at(x, frame_begin.y) = c;
    *tui_cell_at(x, frame_end.y - 1) = c;
  }
  for (size_t y = frame_begin.y; y < frame_end.y; ++y) {
    *tui_cell_at(frame_begin.x, y) = c;
    *tui_cell_at(frame_end.x - 1, y) = c;
  }
}

/*++++++++++++++++++++++++++++++++++++++++++++++++*/
void draw_info_bar(GameState* gs) {
  char buf[255];
  char shortcut[6][255];
  if (gs->mode == PLAY) {
    gs->play_time = get_time() - gs->start_time;
  }
  sprintf(buf, "%d SECONDS", gs->play_time);
  tui_set_str_at(1, gs->play_field_end.y + 3, buf, FG_WHITE, BG_BLACK);
  sprintf(shortcut[0], "SHORTCUTS");
  tui_set_str_at(1, gs->play_field_end.y + 5, shortcut[0], FG_YELLOW, BG_BLACK);

  sprintf(shortcut[1], "  Q      BACK TO MAIN MENU");
  tui_set_str_at(1, gs->play_field_end.y + 6, shortcut[1], FG_WHITE, BG_BLACK);

  sprintf(shortcut[2], "  WSAD   MOVE CURSOR");
  tui_set_str_at(1, gs->play_field_end.y + 7, shortcut[2], FG_WHITE, BG_BLACK);

  sprintf(shortcut[3], "  SPACE  UNCOVER FIELD");
  tui_set_str_at(1, gs->play_field_end.y + 8, shortcut[3], FG_WHITE, BG_BLACK);

  sprintf(shortcut[4], "  F      FLAG FIELD");
  tui_set_str_at(1, gs->play_field_end.y + 9, shortcut[4], FG_WHITE, BG_BLACK);

  sprintf(shortcut[5], "%s", gs->endgame_info);
  tui_set_str_at(1, gs->play_field_end.y + 11, shortcut[5], FG_RED, BG_BLACK);
}

bool is_field_coordinate(GameState* gs, int x, int y) {
  bool x_is_valid = gs->play_field_begin.x <= x && x <= gs->play_field_end.x;
  bool y_is_valid = gs->play_field_begin.y <= y && y <= gs->play_field_end.y;
  return x_is_valid && y_is_valid;
}

/*++++++++++++++++++++++++++++++++++++++++++++++++*/
Cell* field_cell_at(GameState* gs, int x, int y) {
  /* Same as `assert(is_field_coordinate(gs, x, y))` but prints a stack trace if
   * used with the address sanitizer.
   *
   * The stack trace allows you to find out which function call caused the
   * invalid coordinates, which greatly simplifies debugging.
   * (You will probably run into this.)
   *
   * To get the stack trace, we use an ugly hack: if the assertion fails, we
   * simply cause a segmentation fault by writing to the NULL-Pointer, which the
   * address sanitizer then detects and spits out a stack trace for us :3
   */
  if (!is_field_coordinate(gs, x, y)) {
    tui_shutdown();
    printf(FG_RED "ASSERTION FAILED: Coordinate (%d, %d) is not a valid game "
                  "field coordinate.\n\n" COLOR_RESET,
           x, y);
    fflush(stdout);
    int* null = NULL;
    *null = 42;
  }
  return tui_cell_at(x + gs->play_field_begin.x, y + gs->play_field_begin.y);
}

void save_highscore(GameState* gs) {
  H_score* h_scores = malloc_or_exit(sizeof(H_score));
  *h_scores = (H_score){.points = gs->points,
                        .height = gs->play_field_height,
                        .width = gs->play_field_width,
                        .probability = (double)gs->probability,
                        .play_time = gs->play_time};
  vec_push(gs->highscores, h_scores);

  JsonValue* h_json = convert_highscores_vec_to_value(gs);
  FILE* file = fopen("highscores.json", "w");
  json_to_file(h_json, file);
  fclose(file);
  json_value_free(h_json);
}

bool handle_input(GameState* gs, char c) {
  switch (c) {
  case 'q':
    if (gs->mode == PLAY) {
      reset_game(gs, gs->mines);
      reset_game(gs, gs->no_mines);
      reset_game(gs, gs->flags);
      game_matrix_free(gs->new_game);
    }
    gs->mode = MENU;
    break;
  case 'w':
    if (gs->cursor_pos.y > gs->play_field_begin.y) {
      gs->cursor_pos.y--;
    }
    break;
  case 'a':
    if (gs->cursor_pos.x > gs->play_field_begin.x) {
      gs->cursor_pos.x--;
    }
    break;
  case 's':
    if (gs->cursor_pos.y < gs->play_field_end.y) {
      gs->cursor_pos.y++;
    }
    break;
  case 'd':
    if (gs->cursor_pos.x < gs->play_field_end.x) {
      gs->cursor_pos.x++;
    }
    break;
  case 'f':
    if (gs->mode == PLAY) {
      if (game_matrix_at(gs->game_field, gs->cursor_pos.x - 2,
                         gs->cursor_pos.y - 2)
              ->content == '.') {
        *game_matrix_at(gs->game_field, gs->cursor_pos.x - 2,
                        gs->cursor_pos.y - 2) = (Cell){
            .content = 'X', .text_color = FG_RED, .background_color = BG_BLACK};
        gs->count_flags++;
      } else if (game_matrix_at(gs->game_field, gs->cursor_pos.x - 2,
                                gs->cursor_pos.y - 2)
                     ->content == 'X') {
        *game_matrix_at(gs->game_field, gs->cursor_pos.x - 2,
                        gs->cursor_pos.y - 2) =
            (Cell){.content = '.',
                   .text_color = FG_WHITE,
                   .background_color = BG_BLACK};
        gs->count_flags--;
      }
      if (is_winner(gs)) {
        gs->mode = PAUSE;
        game_matrix_free(gs->new_game);
        gs->endgame_info = "** CONGRATULATIONS **";
        reset_game(gs, gs->mines);
        reset_game(gs, gs->no_mines);
        reset_game(gs, gs->flags);
        gs->points = gs->play_field_width * gs->play_field_height *
                     gs->probability * (1000.0 / gs->play_time);
        save_highscore(gs);
      }
    }
    break;
  case ' ':

    if (gs->mode == PLAY) {
      if (game_matrix_at(gs->game_field, gs->cursor_pos.x - 2,
                         gs->cursor_pos.y - 2)
              ->content != 'X') {

        *game_matrix_at(gs->game_field, gs->cursor_pos.x - 2,
                        gs->cursor_pos.y - 2) =
            *game_matrix_at(gs->new_game, gs->cursor_pos.x - 2,
                            gs->cursor_pos.y - 2);
        if (cell_content(gs->new_game, gs->cursor_pos.x - 2,
                         gs->cursor_pos.y - 2) == ' ') {
          open_safe_cells(gs, gs->cursor_pos.x - 2, gs->cursor_pos.y - 2);
        } else if (cell_content(gs->new_game, gs->cursor_pos.x - 2,
                                gs->cursor_pos.y - 2) == '*') {
          copy_content(gs, gs->game_field, gs->new_game);
          game_matrix_free(gs->new_game);

          gs->mode = PAUSE;
          gs->endgame_info = "GAME OVER!";
          reset_game(gs, gs->mines);
          reset_game(gs, gs->no_mines);
          reset_game(gs, gs->flags);
          gs->explosion = true;
        }
        if (is_winner(gs) && !gs->explosion) {
          gs->mode = PAUSE;
          game_matrix_free(gs->new_game);
          gs->endgame_info = "** CONGRATULATIONS **";
          reset_game(gs, gs->mines);
          reset_game(gs, gs->no_mines);
          reset_game(gs, gs->flags);
          gs->points = gs->play_field_width * gs->play_field_height *
                       gs->probability * (1000.0 / gs->play_time);
          save_highscore(gs);
        }
      } // end of next if check for cell
    }   // end of external if check for play
    break;
  } // end of switch
  return false;
}

void reset_game(GameState* gs, Vec* vector) {
  while (vec_length(vector) > 0) {
    vec_pop(vector);
  }
  gs->count_flags = 0;
}

char cell_content(GameMatrix* m, int x, int y) {
  return game_matrix_at(m, x, y)->content;
}

void draw_cursor(GameState* gs) {
  char* fg_color = FG_BLACK;
  char* bg_color = BG_WHITE;
  if (tui_cell_at(gs->cursor_pos.x, gs->cursor_pos.y)->content == ' ') {
    fg_color = FG_WHITE;
  } else if (tui_cell_at(gs->cursor_pos.x, gs->cursor_pos.y)->content == 'X') {
    fg_color = FG_GREEN;
  } else if (tui_cell_at(gs->cursor_pos.x, gs->cursor_pos.y)->content == '*') {
    fg_color = FG_RED;
  }
  Cell c = (Cell){.content =
                      tui_cell_at(gs->cursor_pos.x, gs->cursor_pos.y)->content,
                  .text_color = fg_color,
                  .background_color = bg_color};
  *tui_cell_at(gs->cursor_pos.x, gs->cursor_pos.y) = c;
}

void draw_new_game(GameState* gs) {
  game_matrix_free(gs->game_field);
  gs->explosion = false;
  Cell c = (Cell){
      .content = '.', .text_color = FG_WHITE, .background_color = BG_BLACK};
  gs->game_field =
      game_matrix_new(gs->play_field_width, gs->play_field_height, &c);
  draw_default(gs);
  create_new_game(gs);
}

void draw_default(GameState* gs) {
  for (size_t row = 0; row < gs->play_field_height; row++) {
    for (size_t col = 0; col < gs->play_field_width; col++) {
      *tui_cell_at(gs->play_field_begin.x + col, gs->play_field_begin.y + row) =
          *game_matrix_at(gs->game_field, col, row);
    }
  }
}

void create_new_game(GameState* gs) {
  Cell safe = (Cell){
      .content = ' ', .text_color = FG_BLACK, .background_color = BG_BLACK};
  Cell boom = (Cell){
      .content = '*', .text_color = FG_RED, .background_color = BG_BLACK};
  gs->new_game =
      game_matrix_new(gs->play_field_width, gs->play_field_height, &safe);
  for (size_t row = 0; row < gs->play_field_height; row++) {
    for (size_t col = 0; col < gs->play_field_width; col++) {
      if (rand() % (int)(1 / gs->probability) ==
          (int)(1 / gs->probability) / 2) {
        *game_matrix_at(gs->new_game, col, row) = boom;
      }
    }
  }
  update_cells_status(gs);
}

void update_cells_status(GameState* gs) {
  char c[2];
  int count;
  for (size_t row = 0; row < gs->play_field_height; row++) {
    for (size_t col = 0; col < gs->play_field_width; col++) {
      if (game_matrix_at(gs->new_game, col, row)->content == '*') {
        Int2* mine = malloc(sizeof(Int2));
        if (mine == NULL) {
          exit(1);
        }
        *mine = (Int2){.x = col, .y = row};
        vec_push(gs->mines, mine);
        continue;
      }
      count = count_mines(gs, col, row, '*');
      if (count != 0) {
        sprintf(c, "%d", count);
        *game_matrix_at(gs->new_game, col, row) =
            (Cell){.content = c[0],
                   .text_color = FG_WHITE,
                   .background_color = BG_BLACK};
      }
    }
  }
}

int count_mines(GameState* gs, int x, int y, char c) {
  int count = 0;
  for (int row = -1; row < 2; row++) {
    for (int col = -1; col < 2; col++) {
      if ((row == 0 && col == 0) ||
          !is_field_coordinate(gs, gs->play_field_begin.x + x + col,
                               gs->play_field_begin.y + y + row)) {
        continue;
      }
      if (game_matrix_at(gs->new_game, x + col, y + row)->content == c) {
        count++;
      }
    }
  }
  return count;
}

void copy_content(GameState* gs, GameMatrix* dest, GameMatrix* source) {
  for (int row = 0; row < gs->play_field_height; row++) {
    for (int col = 0; col < gs->play_field_width; col++) {
      *game_matrix_at(dest, col, row) = *game_matrix_at(source, col, row);
    }
  }
}

void open_safe_cells(GameState* gs, int x, int y) {
  Cell c = (Cell){
      .content = ' ', .text_color = FG_WHITE, .background_color = BG_BLACK};
  GameMatrix* copy =
      game_matrix_new(gs->play_field_width, gs->play_field_height, &c);
  /* Copy cells temporarily */
  copy_content(gs, copy, gs->new_game);

  /* Cell coordinates */
  Int2* coordinate = malloc(sizeof(Int2));
  *coordinate = (Int2){.x = x, .y = y};
  if (coordinate == NULL) {
    exit(1);
  }
  vec_push(gs->no_mines, coordinate);
  *game_matrix_at(gs->game_field, x, y) = *game_matrix_at(copy, x, y);
  // char ct[2];
  // int count = 64;
  /* Check all the neighbouring safe cells with no mines */
  while (vec_length(gs->no_mines) > 0) {
    /*++count;
    if (count > 121) {
      count = 65;
    }*/
    // sprintf(ct, "%c", count);
    Int2* co = *vec_at(gs->no_mines, 0);
    game_matrix_at(copy, co->x, co->y)->content = 'f';
    game_matrix_at(copy, co->x, co->y)->text_color = FG_YELLOW;

    *game_matrix_at(gs->game_field, co->x, co->y) =
        *game_matrix_at(gs->new_game, co->x, co->y);
    free_safe_cells(gs, co->x, co->y, copy);

    vec_remove(gs->no_mines, 0);
  }

  /* free the copy */
  if (copy != NULL) {
    game_matrix_free(copy);
  }
}

void free_safe_cells(GameState* gs, int x, int y, GameMatrix* m) {
  // char ct[2];
  // int count = 64;
  for (int row = -1; row < 2; row++) {
    for (int col = -1; col < 2; col++) {
      //
      if ((row == 0 && col == 0) ||
          !is_field_coordinate(gs, gs->play_field_begin.x + x + col,
                               gs->play_field_begin.y + y + row)) {
        continue;
      }

      if (game_matrix_at(m, x + col, y + row)->content == ' ') {
        Int2* coordinate = malloc(sizeof(Int2));
        if (coordinate == NULL) {
          exit(1);
        }

        *coordinate = (Int2){.x = x + col, .y = y + row};
        vec_push(gs->no_mines, coordinate);

        game_matrix_at(m, coordinate->x, coordinate->y)->content = 'f';
        game_matrix_at(m, coordinate->x, coordinate->y)->text_color = FG_YELLOW;
      }
      *game_matrix_at(gs->game_field, x + col, y + row) =
          *game_matrix_at(gs->new_game, x + col, y + row);
    }
  }
}

int count_safe_cells(GameState* gs) {
  int count = 0;
  for (int row = 0; row < gs->play_field_height; row++) {
    for (int col = 0; col < gs->play_field_width; col++) {
      if (game_matrix_at(gs->game_field, col, row)->content == ' ') {
        count++;
      }
    }
  }
  return count;
} // end of function

bool is_winner(GameState* gs) {
  if (gs->count_flags == vec_length(gs->mines) && is_all_visited(gs)) {
    for (int i = 0; i < vec_length(gs->mines); i++) {
      Int2* mine = *vec_at(gs->mines, i);
      /* If Flag is set at wrong position the game is not won */
      if (game_matrix_at(gs->game_field, mine->x, mine->y)->content != 'X') {
        return false;
      }
    }

    return true;
  }
  if (count_safe_cells(gs) ==
      game_matrix_width(gs->game_field) * game_matrix_height(gs->game_field)) {
    return true;
  }
  return false;
}

bool is_all_visited(GameState* gs) {
  for (int row = 0; row < gs->play_field_height; row++) {
    for (int col = 0; col < gs->play_field_width; col++) {
      if (game_matrix_at(gs->game_field, col, row)->content == '.') {
        return false;
      }
    }
  }
  return true;
}
