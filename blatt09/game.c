#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "../tui/tui.h"
#include "./game_highscores.h"
#include "./game_lib.h"
#include "./memtools.h"
#include "./vec.h"

const char* logo[] = {
    "      __        ________  ___________  _______   _______     ______    __ "
    "    ________    ________ ",
    "     /\"\"\\      /\"       )(\"     _   \")/\"     \"| /\"      \\   /   "
    " \" \\  |\" \\   |\"      \"\\  /\"       )",
    "    /    \\    (:   \\___/  )__/  \\\\__/(: ______)|:        | // ____  "
    "\\ ||  |  (.  ___  :)(:   \\___/ ",
    "   /' /\\  \\    \\___  \\       \\\\_ /    \\/    |  |_____/   )/  /    "
    ") :)|:  |  |: \\   ) || \\___  \\   ",
    "  //  __'  \\    __/  \\\\      |.  |    // ___)_  //      /(: (____/ // "
    "|.  |  (| (___\\ ||  __/  \\\\  ",
    " /   /  \\\\  \\  /\" \\   :)     \\:  |   (:      \"||:  __   \\ \\      "
    "  /  /\\  |\\ |:       :) /\" \\   :) ",
    "(___/    \\___)(_______/       \\__|    \\_______)|__|  \\___) \\\"_____/ "
    " (__\\_|_)(________/ (_______/  ",
    NULL};

Int2 get_logo_size(void) {
  Int2 size = {0, 0};
  for (const char** line = logo; *line != NULL; ++line) {
    size.y++;
    int width = strlen(*line);
    if (width > size.x) {
      size.x = width;
    }
  }
  return size;
}

void tui_print_centered(Int2* center, int y, char* s, char* fg, char* bg) {
  tui_set_str_at(center->x - strlen(s) / 2, y, s, fg, bg);
}

GameState* new_game_state(Size2 term_size) {
  /* The game field starts at position {1, 1}. This accounts for the white frame
   * drawn around the game field.
   *
   * The game field ends a few rows above the bottom of the terminal, so we have
   * space to render the info text (see screenshots).
   */
  Int2 field_begin = {1, 1};
  Int2 field_end = {term_size.x - 1, term_size.y - 3};
  Int2 field_size = {field_end.x - field_begin.x, field_end.y - field_begin.y};

  /* Initialize the game state, which you have to manipulate in the functions
   * from game_lib.c. The GameState-struct is defined and documented in
   * game_lib.h. */
  GameState* game_state = malloc(sizeof(GameState));
  if (game_state == NULL) {
    return NULL;
  }
  *game_state = (GameState){
      .term_size = {term_size.x, term_size.y}, /* Convert Size2 to Int2. */
      .field_begin = field_begin,
      .field_end = field_end,
      .field_size = field_size,
      .ship =
          {
              .pos = {1, field_size.y /
                             2}, /* At the beginning, the ship is positioned */
              .health = 3,       /* left to the center of the game field. */
              .powerup_time = 0,
          },
      .points = 0,
      .projectiles = vec_new(),
      .asteroids = vec_new(),
      .powerups = vec_new(),
      .explosions = vec_new(),
      .time_step = 0,
  };
  return game_state;
}

void free_game_state(GameState* gs) {
  for (size_t i = 0; i < vec_length(gs->explosions); ++i) {
    free(*vec_at(gs->explosions, i));
  }
  for (size_t i = 0; i < vec_length(gs->powerups); ++i) {
    free(*vec_at(gs->powerups, i));
  }
  for (size_t i = 0; i < vec_length(gs->asteroids); ++i) {
    free(*vec_at(gs->asteroids, i));
  }
  for (size_t i = 0; i < vec_length(gs->projectiles); ++i) {
    free(*vec_at(gs->projectiles, i));
  }
  vec_free(gs->explosions);
  vec_free(gs->powerups);
  vec_free(gs->asteroids);
  vec_free(gs->projectiles);
  free(gs);
}

GameState* new_game(Size2 term_size) {
  GameState* game_state = new_game_state(term_size);
  if (game_state == NULL) {
    return NULL;
  }

  while (1) {
    /* Handle Keyboard Input */

    if (stdin_has_changed()) {
      char c = read_from_stdin();
      if (handle_input(game_state, c)) {
        free_game_state(game_state);
        return NULL;
      }
    }

    /* Update the GameState. */

    move_projectiles(game_state);
    handle_projectile_asteroid_collisions(game_state);

    move_asteroids(game_state);
    spawn_asteroids(game_state);
    handle_projectile_asteroid_collisions(game_state);
    handle_asteroid_ship_collisions(game_state);

    move_powerups(game_state);
    spawn_powerups(game_state);
    handle_powerup_ship_collisions(game_state);

    move_explosions(game_state);

    /* Exit the game, if the ship was hit by enough asteroids. */
    if (game_state->ship.health <= 0) {
      return game_state;
    }

    /* If the ship currently has a powerup, decrease the time
     * until the powerup is gone. */
    if (game_state->ship.powerup_time > 0) {
      game_state->ship.powerup_time--;
    }

    /* Draw the GameState in the terminal. */

    tui_clear();

    draw_info_bar(game_state);
    draw_frame(game_state);
    draw_ship(game_state);
    draw_projectiles(game_state);
    draw_asteroids(game_state);
    draw_powerups(game_state);
    draw_explosions(game_state);

    tui_update();

    /* Increase time step and wait for 10000 µs (0.01 s). */

    game_state->time_step++;

    usleep(10000);
  }
}

void draw_highscores_at(size_t x, size_t y, Vec* highscores) {
  if (highscores == NULL) {
    tui_set_str_at(x, y, "ERROR: Failed to read highscores from JSON.", FG_RED,
                   BG_BLACK);
  } else {
    char buf[32];
    tui_set_str_at(x, y, "RANK", FG_BOLD_WHITE, BG_BLACK);
    tui_set_str_at(x + 10, y, "NAME", FG_BOLD_WHITE, BG_BLACK);
    tui_set_str_at(x + 20, y, "POINTS", FG_BOLD_WHITE, BG_BLACK);
    tui_set_str_at(x + 30, y, "DISTANCE", FG_BOLD_WHITE, BG_BLACK);
    for (size_t i = 0; i < vec_length(highscores); ++i) {
      if (i >= 10) {
        break;
      }
      sprintf(buf, "#%ld", i + 1);
      tui_set_str_at(x, y + 1 + i, buf, FG_WHITE, BG_BLACK);
      Highscore* h = *vec_at(highscores, i);
      tui_set_str_at(x + 10, y + 1 + i, h->name, FG_WHITE, BG_BLACK);
      sprintf(buf, "%d", h->points);
      tui_set_str_at(x + 20, y + 1 + i, buf, FG_WHITE, BG_BLACK);
      sprintf(buf, "%d", h->distance);
      tui_set_str_at(x + 30, y + 1 + i, buf, FG_WHITE, BG_BLACK);
    }
  }
}

Vec* download_and_parse_highscores(char* name) {
  JsonValue* v;
  if (name == NULL) {
    v = download_highscore_json();
  } else {
    v = download_highscore_json_for(name);
  }
  if (v == NULL) {
    return NULL;
  }
  Vec* hs = json_to_highscores(v);
  json_value_free(v);
  return hs;
}

/* Returns true, if the game should be closed.
 * Returns false, if a new game should be started.
 */
bool title_screen(Size2 term_size, char* name) {
  /* Create some nice background by drawing some ships flying at different
   * speeds :3 */
  Int2 positions[10];
  int speeds[10];
  for (size_t i = 0; i < 10; ++i) {
    positions[i].x = (rand() % (term_size.x - 16)) + 8;
    positions[i].y = (rand() % (term_size.y - 10)) + 4;
    speeds[i] = (rand() % 3) + 1;
  }
  GameState* fake_gs = new_game_state(term_size);

  Int2 logo_size = get_logo_size();
  Int2 logo_pos = {(term_size.x - logo_size.x) / 2, 0};

  Vec* highscores_all = download_and_parse_highscores(NULL);
  Vec* highscores_name = download_and_parse_highscores(name);

  bool exploded = false;

  /* true, while user is entering a name */
  bool set_name = false;
  size_t cur_name_char = 0;
  while (1) {
    if (stdin_has_changed()) {
      char c = read_from_stdin();
      if (!set_name) {
        if (c == 'q') {
          free_game_state(fake_gs);
          if (highscores_all != NULL) {
            highscores_free(highscores_all);
          }
          if (highscores_name != NULL) {
            highscores_free(highscores_name);
          }
          return true;
        } else if (c == ' ') {
          free_game_state(fake_gs);
          if (highscores_all != NULL) {
            highscores_free(highscores_all);
          }
          if (highscores_name != NULL) {
            highscores_free(highscores_name);
          }
          return false;
        } else if (c == 'n') {
          for (size_t i = 0; i < 6; ++i) {
            name[i] = '_';
          }
          set_name = true;
        } else if (c == 'e') {
          exploded = !exploded;
          if (exploded) {
            for (size_t i = 0; i < 10; ++i) {
              Explosion* e = malloc(sizeof(Explosion));
              e->pos = positions[i];
              e->age = 0;
              vec_push(fake_gs->explosions, e);
            }
          }
        }
      } else {
        if (c == '\n' || c == '\r') {
          name[cur_name_char] = 0;
          cur_name_char = 0;
          set_name = false;
        } else {
          name[cur_name_char++] = c;
          if (cur_name_char == 6) {
            cur_name_char = 0;
            set_name = false;
          }
        }
        if (!set_name) {
          if (highscores_name != NULL) {
            highscores_free(highscores_name);
          }
          highscores_name = download_and_parse_highscores(name);
        }
      }
    }

    tui_clear();

    /* Draw the logo */
    for (size_t i = 0; i < logo_size.y; ++i) {
      tui_set_str_at(logo_pos.x, logo_pos.y + i, logo[i], FG_RED, BG_BLACK);
    }

    /* Draw the text. */
    Int2 center = {term_size.x / 2, term_size.y / 2};
    int highscore_y = logo_pos.y + logo_size.y + 2;
    tui_print_centered(&center, highscore_y, "HIGHSCORES", FG_BOLD_WHITE,
                       BG_BLACK);
    tui_set_str_at(center.x - 35, highscore_y + 2, "GLOBAL", FG_BOLD_WHITE,
                   BG_BLACK);
    tui_set_str_at(center.x + 25, highscore_y + 2, "PERSONAL", FG_BOLD_WHITE,
                   BG_BLACK);
    draw_highscores_at(center.x - 50, highscore_y + 4, highscores_all);
    draw_highscores_at(center.x + 10, highscore_y + 4, highscores_name);
    tui_print_centered(&center, term_size.y - 8, "ASTRONAUT", FG_WHITE,
                       BG_BLACK);
    tui_print_centered(&center, term_size.y - 7, name,
                       set_name ? FG_RED : FG_GREEN, BG_BLACK);
    tui_print_centered(&center, term_size.y - 5,
                       "PRESS SPACE TO START THE GAME", FG_GREEN, BG_BLACK);
    tui_print_centered(&center, term_size.y - 4,
                       "PRESS N TO NAME YOUR ASTRONAUT",
                       set_name ? FG_RED : FG_GREEN, BG_BLACK);
    if (!exploded) {
      tui_print_centered(&center, term_size.y - 3,
                         "PRESS E TO EXPLODE ALL THE THINGS", FG_GREEN,
                         BG_BLACK);
    } else {
      tui_print_centered(&center, term_size.y - 3,
                         "PRESS E TO TRAVEL BACK IN TIME", FG_GREEN, BG_BLACK);
    }
    tui_print_centered(&center, term_size.y - 2, "PRESS Q TO QUIT", FG_GREEN,
                       BG_BLACK);

    /* Draw and move the ships. */
    if (!exploded) {
      for (size_t i = 0; i < 10; ++i) {
        fake_gs->ship.pos.x = positions[i].x;
        fake_gs->ship.pos.y = positions[i].y;
        fake_gs->ship.powerup_time = 0;
        draw_ship(fake_gs);
        positions[i].x += speeds[i];
        if (positions[i].x > term_size.x - 8) {
          positions[i].x -= term_size.x - 8;
        }
      }
    }
    draw_explosions(fake_gs);
    move_explosions(fake_gs);

    tui_update();

    usleep(30000);
  }
}

void draw_game_over_screen(Size2 term_size, GameState* gs, char* name) {
  tui_clear();

  Int2 center = {term_size.x / 2, term_size.y / 2};
  tui_print_centered(&center, center.y - 3, "GAME OVER", FG_RED, BG_BLACK);

  char buf[255];
  sprintf(buf, "ASTRONAUT: %s", name);
  tui_print_centered(&center, center.y - 1, buf, FG_WHITE, BG_BLACK);
  sprintf(buf, "POINTS: %d", gs->points);
  tui_print_centered(&center, center.y + 0, buf, FG_WHITE, BG_BLACK);
  sprintf(buf, "DISTANCE: %d", gs->time_step);
  tui_print_centered(&center, center.y + 1, buf, FG_WHITE, BG_BLACK);

  tui_print_centered(&center, center.y + 3, "PRESS SPACE TO CONTINUE", FG_GREEN,
                     BG_BLACK);

  tui_update();
}

void game_over_screen(Size2 term_size, GameState* gs, char* name) {
  Highscore highscore = (Highscore){
      .name = name,
      .points = gs->points,
      .distance = gs->time_step,
  };

  JsonValue* highscore_json = highscore_to_json(&highscore);
  if (highscore_json != NULL) {
    upload_highscore_json(highscore_json);
    json_value_free(highscore_json);
  }

  draw_game_over_screen(term_size, gs, name);

  /* Wait for 2 seconds to not skip if user mashes keys while dying. */
  usleep(2000000);

  /* Read all keys in the buffer to not skip the next screen (again for key
   * mashing) */
  while (stdin_has_changed()) {
    read_from_stdin();
  }

  while (1) {
    if (stdin_has_changed()) {
      char c = read_from_stdin();
      if (c == ' ' || c == 'q') {
        return;
      }
    }

    /* Wait for 2 seconds to not skip if user mashes keys while dying. */
    usleep(10000);
  }
}

int main(void) {
  tui_init();

  /* Initialize the random number generator with the current time, such that
   * `rand()` produces different random numbers every time we run the program.
   */
  srand(time(NULL));

  /* We require that the terminal window has space for at least 40 columns and
   * 20 rows. Otherwise, we exit the programm with an error message.
   * We assume that the terminal size doesn't change after the game has started.
   */
  Size2 min_term_size = {90, 28};
  Size2 term_size = tui_size();
  if (term_size.x < min_term_size.x || term_size.y < min_term_size.y) {
    tui_shutdown();
    printf("ERROR: terminal has to be at least of size %lu x %lu but is of "
           "size %lu x %lu.\n",
           min_term_size.x, min_term_size.y, term_size.x, term_size.y);
    exit(1);
  }

  char name[7] = "XXXXXX";

  while (1) {
    bool quit = title_screen(term_size, name);
    if (quit) {
      break;
    }

    GameState* game_over_state = new_game(term_size);
    if (game_over_state) {
      game_over_screen(term_size, game_over_state, name);
      free_game_state(game_over_state);
    }
  }

  tui_shutdown();

  return 0;
}
