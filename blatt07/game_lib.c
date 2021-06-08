#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

#include "../tui/tui.h"

#include "./game_lib.h"

void draw_info_bar(GameState* gs) {
  char buf[255];
  sprintf(buf, "LIFES: %d    POINTS: %d    DISTANCE: %d    POWERUP: %d",
          gs->ship.health, gs->points, gs->time_step, gs->ship.powerup_time);
  tui_set_str_at(0, gs->term_size.y - 1, buf, FG_WHITE, BG_BLACK);
}

void draw_frame(GameState* gs) {
  Cell c = (Cell){
      .content = ' ', .text_color = FG_WHITE, .background_color = BG_WHITE};
  Int2 frame_begin = {gs->field_begin.x - 1, gs->field_begin.y - 1};
  Int2 frame_end = {gs->field_end.x + 1, gs->field_end.y + 1};
  for (size_t x = frame_begin.x; x < frame_end.x; ++x) {
    *tui_cell_at(x, frame_begin.y) = c;
    *tui_cell_at(x, frame_end.y - 1) = c;
  }
  for (size_t y = frame_begin.y; y < frame_end.y; ++y) {
    *tui_cell_at(frame_begin.x, y) = c;
    *tui_cell_at(frame_end.x - 1, y) = c;
  }
}

bool is_field_coordinate(GameState* gs, int x, int y) {
  Int2 size = gs->field_size;
  bool x_is_valid = 0 <= x && x < size.x;
  bool y_is_valid = 0 <= y && y < size.x;
  return x_is_valid && y_is_valid;
}

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
    printf(FG_RED "ASSERTION FAILED: Coordinate (%d, %d) is not a valid game field coordinate.\n\n" COLOR_RESET, x, y);
    fflush(stdout);
    int* null = NULL;
    *null = 42;
  }

  return tui_cell_at(x + gs->field_begin.x, y + gs->field_begin.y);
}

void draw_ship(GameState* gs) {
  /* TODO */
}

void draw_projectiles(GameState* gs) {
  /* TODO */
}

void draw_asteroids(GameState* gs) {
  /* TODO */
}

void draw_powerups(GameState* gs) {
  /* TODO */
}

void draw_explosions(GameState* gs) {
  /* TODO */
}

bool handle_input(GameState* gs, char c) {
  /* TODO */

  if (c == 'q')
    return true;

  return false;
}

bool collides_with_ship(Int2 ship_pos, Int2 pos) {
  /* TODO */
  return false;
}

void move_projectiles(GameState* gs) {
  /* TODO */
}

void move_asteroids(GameState* gs) {
  /* TODO */
}

void move_powerups(GameState* gs) {
  /* TODO */
}

void move_explosions(GameState* gs) {
  /* TODO */
}

void spawn_asteroids(GameState* gs) {
  /* TODO */
}

void spawn_powerups(GameState* gs) {
  /* TODO */
}

void handle_projectile_asteroid_collisions(GameState* gs) {
  /* TODO */
}

void handle_powerup_ship_collisions(GameState* gs) {
  /* TODO */
}

void handle_asteroid_ship_collisions(GameState* gs) {
  /* TODO */
}
