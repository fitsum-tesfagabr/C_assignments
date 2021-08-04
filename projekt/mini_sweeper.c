#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../tui/tui.h"
#include "./menu.h"
#include "./mini_sweeper_lib.h"
#include "./vec.h"
int main(int argc, char** argv) {

  /* Initialize Terminal */
  tui_init();
  time_t t;
  srand((unsigned)time(&t));

  /* Terminal size must have atleast 60 columns and 30 rows. Else exit! */
  Size2 min_term_size = {60, 30};
  Size2 term_size = tui_size();
  if (term_size.x < min_term_size.x || term_size.y < min_term_size.y) {
    tui_shutdown();
    printf("ERROR: terminal has to be at least of size %lu x %lu.\n",
           min_term_size.x, min_term_size.y);
    exit(1);
  } // end of if

  /* Define Frame */
  Int2 field_begin = {1, 1};
  Int2 field_end = {term_size.x - 1, term_size.y - 1};
  Int2 field_size = {field_end.x - field_begin.x, field_end.y - field_begin.y};

  /* Default cell */
  Cell c = (Cell){
      .content = '.', .text_color = FG_WHITE, .background_color = BG_BLACK};
  /* Initialize the game state */
  GameState game_state = {
      .term_size = {term_size.x, term_size.y}, /* Convert Size2 to Int2. */
      .field_begin = field_begin,
      .field_end = field_end,
      .field_size = field_size,
      .probability = 0.15,
      .explosion = false,
      .mode = MENU,
      .endgame_info = " ",
      .points = 0,
      .play_time = 1,
      .play_field_width = 15,
      .play_field_height = 15,
      .probability = 0.15,
      .cursor_pos =
          (Int2){game_state.field_begin.x + 1, game_state.field_begin.y + 1},
      .play_field_begin =
          (Int2){game_state.field_begin.x + 1, game_state.field_begin.y + 1},
      .mines = vec_new(),
      .flags = vec_new(),
      .count_flags = 0,
      .no_mines = vec_new(),
      .time_step = 0,
  };
  FILE* hfile;
  if ((hfile = fopen("highscores.json", "r"))) {
    fclose(hfile);
    char* file_name = "highscores.json";
    JsonValue* json = file_to_json(file_name);
    if (json != NULL) {
      game_state.highscores = json_to_highscores(json);
    }
    json_value_free(json);
  } else {
    game_state.highscores = vec_new();
  }

  /* Load settings from file if exist */
  FILE* file;
  if ((file = fopen("settings.tsv", "r"))) {
    if (file == NULL) {
      exit(1);
    }
    read_settings(&game_state, file);
    fclose(file);
  } else {
    file = fopen("settings.tsv", "w");
    if (file == NULL) {
      exit(1);
    }

    write_settings(&game_state, file);
    fclose(file);

    file = fopen("settings.tsv", "r");
    read_settings(&game_state, file);
    fclose(file);
  }

  game_state.game_field = game_matrix_new(game_state.play_field_width,
                                          game_state.play_field_height, &c);
  Menu_status menu_state =
      (Menu_status){.menu_cursor_pos_y = 2, .which_section = MAIN};
  while (1) {
    game_state.play_field_end =
        (Int2){game_state.field_begin.x + game_state.play_field_width,
               game_state.field_begin.y + game_state.play_field_height};
    /* Set default game dimention and default cell matrix */
    if (stdin_has_changed()) {
      char c = read_from_stdin();

      if (game_state.mode == MENU) {
        if (handle_menu_input(&game_state, &menu_state, c)) {
          break;
        }
      } else if (handle_input(&game_state, c)) {
        break;
      }

    } // end of if

    /* Update game */

    /*Draw the GameState */
    tui_clear();

    switch (game_state.mode) {
    case MENU:
      draw_menu(&game_state, &menu_state);
      break;
    case PAUSE:
    case PLAY:
      draw_info_bar(&game_state);
      draw_frame(&game_state);
      draw_default(&game_state);
      draw_cursor(&game_state);
      break;
    }
    tui_update();

    /* Increase time step */
    game_state.time_step++;

    /*Wait for 0.01s */
    usleep(10000);

  } // end of while
  exit_safely(&game_state);
  return 0;
} // end of main

void exit_safely(GameState* gs) {
  vec_free(gs->mines);
  vec_free(gs->flags);
  vec_free(gs->no_mines);
  vec_free(gs->highscores);
  game_matrix_free(gs->game_field);
  tui_shutdown();
}
