#include <assert.h>
#include <stdlib.h>

#include "../tui/tui.h"

#include "./game_lib.h"
#include "./memtools.h"

void draw_info_bar(GameState* gs) {
  char buf[255];
  sprintf(buf, "LIFES: %d    POINTS: %d   DISTANCE: %d    POWERUP: %d",
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
  bool x_is_valid = 0 <= x && x < gs->field_size.x;
  bool y_is_valid = 0 <= y && y < gs->field_size.y;
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
    printf(FG_RED "ASSERTION FAILED: Coordinate (%d, %d) is not a valid game "
                  "field coordinate.\n\n" COLOR_RESET,
           x, y);
    fflush(stdout);
    int* null = NULL;
    *null = 42;
  }

  return tui_cell_at(x + gs->field_begin.x, y + gs->field_begin.y);
}

void draw_ship(GameState* gs) {
  Cell c = (Cell){
      .content = ' ', .text_color = FG_RED, .background_color = BG_MAGENTA};
  Cell c_burst = (Cell){
      .content = '=', .text_color = FG_YELLOW, .background_color = BG_BLACK};
  Cell c_burst2 = (Cell){
      .content = '-', .text_color = FG_YELLOW, .background_color = BG_BLACK};
  Cell c_peak = (Cell){
      .content = '>', .text_color = FG_YELLOW, .background_color = BG_BLACK};

  size_t x = gs->ship.pos.x;
  size_t y = gs->ship.pos.y;

  *field_cell_at(gs, x, y) = c_burst2;
  *field_cell_at(gs, x, y - 1) = c_burst2;
  *field_cell_at(gs, x, y + 1) = c_burst2;
  *field_cell_at(gs, x + 1, y) = c_burst;
  *field_cell_at(gs, x + 1, y - 1) = c_burst;
  *field_cell_at(gs, x + 1, y + 1) = c_burst;
  *field_cell_at(gs, x + 2, y) = c;
  *field_cell_at(gs, x + 2, y - 1) = c;
  *field_cell_at(gs, x + 2, y + 1) = c;
  *field_cell_at(gs, x + 3, y) = c;
  *field_cell_at(gs, x + 4, y) = c;
  *field_cell_at(gs, x + 5, y) = c_peak;

  bool has_powerup = gs->ship.powerup_time > 0;
  if (has_powerup) {
    *field_cell_at(gs, x + 3, y - 1) = c_peak;
    *field_cell_at(gs, x + 3, y + 1) = c_peak;
  }
}

void draw_projectiles(GameState* gs) {
  for (size_t i = 0; i < vec_length(gs->projectiles); ++i) {
    Int2* projectile = *vec_at(gs->projectiles, i);
    Cell c = (Cell){
        .content = '>', .text_color = FG_RED, .background_color = BG_BLACK};
    *field_cell_at(gs, projectile->x, projectile->y) = c;
  }
}

void draw_asteroids(GameState* gs) {
  Cell c = (Cell){
      .content = ' ', .text_color = FG_WHITE, .background_color = BG_WHITE};
  for (size_t i = 0; i < vec_length(gs->asteroids); ++i) {
    Int2* asteroid = *vec_at(gs->asteroids, i);
    *field_cell_at(gs, asteroid->x, asteroid->y) = c;
  }
}

void draw_powerups(GameState* gs) {
  Cell c = (Cell){
      .content = '@', .text_color = FG_GREEN, .background_color = BG_BLACK};
  for (size_t i = 0; i < vec_length(gs->powerups); ++i) {
    Int2* powerup = *vec_at(gs->powerups, i);
    *field_cell_at(gs, powerup->x, powerup->y) = c;
  }
}

void draw_explosions(GameState* gs) {
  Cell c = (Cell){
      .content = '#', .text_color = FG_YELLOW, .background_color = BG_RED};
  for (size_t i = 0; i < vec_length(gs->explosions); ++i) {
    Explosion* e = *vec_at(gs->explosions, i);
    Int2 pos1 = {e->pos.x + e->age * 2, e->pos.y};
    Int2 pos2 = {e->pos.x - e->age * 2, e->pos.y};
    Int2 pos3 = {e->pos.x, e->pos.y + e->age};
    Int2 pos4 = {e->pos.x, e->pos.y - e->age};
    if (is_field_coordinate(gs, pos1.x, pos1.y))
      *field_cell_at(gs, pos1.x, pos1.y) = c;
    if (is_field_coordinate(gs, pos2.x, pos2.y))
      *field_cell_at(gs, pos2.x, pos2.y) = c;
    if (is_field_coordinate(gs, pos3.x, pos3.y))
      *field_cell_at(gs, pos3.x, pos3.y) = c;
    if (is_field_coordinate(gs, pos4.x, pos4.y))
      *field_cell_at(gs, pos4.x, pos4.y) = c;
  }
}

bool handle_input(GameState* gs, char c) {
  if (c == 'w' || c == 'i') {
    if (gs->ship.pos.y > 2) {
      gs->ship.pos.y -= 1;
    }
  }
  if (c == 's' || c == 'k') {
    if (gs->ship.pos.y < gs->field_size.y - 3) {
      gs->ship.pos.y += 1;
    }
  }
  if (c == 'a' || c == 'j') {
    if (gs->ship.pos.x > 1) {
      gs->ship.pos.x -= 1;
    }
  }
  if (c == 'd' || c == 'l') {
    if (gs->ship.pos.x < gs->field_size.x - 7) {
      gs->ship.pos.x += 1;
    }
  }
  if (c == ' ') {
    Int2* p = malloc(sizeof(Int2));
    if (p == NULL) {
      exit(1);
    }
    p->x = gs->ship.pos.x + 5;
    p->y = gs->ship.pos.y;
    vec_push(gs->projectiles, p);
    if (gs->ship.powerup_time > 0) {
      Int2* p1 = malloc(sizeof(Int2));
      if (p1 == NULL) {
        exit(1);
      }
      p1->x = gs->ship.pos.x + 3;
      p1->y = gs->ship.pos.y - 1;
      vec_push(gs->projectiles, p1);
      Int2* p2 = malloc(sizeof(Int2));
      if (p2 == NULL) {
        exit(1);
      }
      p2->x = gs->ship.pos.x + 3;
      p2->y = gs->ship.pos.y + 1;
      vec_push(gs->projectiles, p2);
    }
  }
  if (c == 'q')
    return true;

  return false;
}

bool collides_with_ship(Int2 ship_pos, Int2 pos) {
  if (ship_pos.x + 2 == pos.x && ship_pos.y - 1 <= pos.y &&
      pos.y <= ship_pos.y + 1)
    return true;
  if (ship_pos.x + 3 == pos.x && ship_pos.y == pos.y)
    return true;
  return false;
}

void move_projectiles(GameState* gs) {
  for (size_t i = 0; i < vec_length(gs->projectiles);) {
    Int2* p = *vec_at(gs->projectiles, i);
    p->x += 1;
    if (p->x >= gs->field_size.x) {
      free(vec_remove(gs->projectiles, i));
    } else {
      i++;
    }
  }
}

void move_asteroids(GameState* gs) {
  if (gs->time_step % 5 == 0) {
    for (size_t i = 0; i < vec_length(gs->asteroids); ++i) {
      Int2* p = *vec_at(gs->asteroids, i);
      p->x -= 1;
      if (p->x == 0) {
        free(vec_remove(gs->asteroids, i));
        i -= 1;
      }
    }
  }
}

void move_powerups(GameState* gs) {
  for (size_t i = 0; i < vec_length(gs->powerups); ++i) {
    Int2* p = *vec_at(gs->powerups, i);
    p->x -= 1;
    if (p->x < 1) {
      free(vec_remove(gs->powerups, i));
      i -= 1;
    }
  }
}

void move_explosions(GameState* gs) {
  for (size_t i = 0; i < vec_length(gs->explosions);) {
    Explosion* e = *vec_at(gs->explosions, i);
    e->age += 1;
    if (e->age > 5) {
      free(vec_remove(gs->explosions, i));
    } else {
      i++;
    }
  }
}

void spawn_asteroids(GameState* gs) {
  if (gs->time_step % 5 == 0) {
    for (size_t y = 0; y < gs->field_size.y; ++y) {
      if (rand() % 50 == 23) {
        Int2* p = malloc(sizeof(Int2));
        if (p == NULL) {
          exit(1);
        }
        p->x = gs->field_size.x - 1;
        p->y = y;
        vec_push(gs->asteroids, p);
      }
    }
  }
}

void spawn_powerups(GameState* gs) {
  if (rand() % 200 == 0) {
    Int2* p = malloc(sizeof(Int2));
    if (p == NULL) {
      exit(1);
    }
    p->x = gs->field_size.x - 1;
    p->y = rand() % gs->field_size.y;
    vec_push(gs->powerups, p);
  }
}

void handle_projectile_asteroid_collisions(GameState* gs) {
  for (size_t i = 0; i < vec_length(gs->projectiles); ++i) {
    for (size_t j = 0; j < vec_length(gs->asteroids); ++j) {
      Int2* p = *vec_at(gs->projectiles, i);
      Int2* a = *vec_at(gs->asteroids, j);
      if (p->x == a->x && p->y == a->y) {
        Explosion* e = malloc_or_exit(sizeof(Explosion));
        e->pos = *p;
        e->age = 0;
        vec_push(gs->explosions, e);
        free(vec_remove(gs->projectiles, i));
        free(vec_remove(gs->asteroids, j));
        i--;
        gs->points += 5;
        break;
      }
    }
  }
}

void handle_powerup_ship_collisions(GameState* gs) {
  for (size_t i = 0; i < vec_length(gs->powerups); ++i) {
    Int2* p = *vec_at(gs->powerups, i);
    if (p->x == gs->ship.pos.x && p->y == gs->ship.pos.y) {
      gs->ship.powerup_time = 1000;
      free(vec_remove(gs->powerups, i));
      i -= 1;
      gs->points += 50;
    }
  }
}

void handle_asteroid_ship_collisions(GameState* gs) {
  for (size_t i = 0; i < vec_length(gs->asteroids);) {
    Int2* p = *vec_at(gs->asteroids, i);
    if (collides_with_ship(gs->ship.pos, *p)) {
      gs->ship.health--;
      Explosion* e = malloc(sizeof(Explosion));
      if (e == NULL) {
        exit(1);
      }
      e->pos = *p;
      e->age = 0;
      vec_push(gs->explosions, e);
      free(vec_remove(gs->asteroids, i));
    } else {
      ++i;
    }
  }
}
