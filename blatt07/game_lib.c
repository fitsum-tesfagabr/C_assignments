#include "../tui/tui.h"
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "./game_lib.h"

/*++++++++++++++++++++++++++++++++++++++++++++++++*/
void draw_info_bar(GameState* gs) {
  char buf[255];
  sprintf(buf,
          "LIFES: %d    POINTS: %d    DISTANCE: %d    POWERUP: %d",
          gs->ship.health, gs->points, gs->time_step, gs->ship.powerup_time);
  tui_set_str_at(0, gs->term_size.y - 1, buf, FG_WHITE, BG_BLACK);
}

/*++++++++++++++++++++++++++++++++++++++++++++++++*/
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
  bool y_is_valid = 0 <= y && y < size.y;
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

  return tui_cell_at(x + gs->field_begin.x, y + gs->field_begin.y);
}

/*++++++++++++++++++++++++++++++++++++++++++++++++*/
void draw_ship(GameState* gs) {
  /* Check if Ship is inside Boundry */
  if (is_field_coordinate(gs, gs->ship.pos.x, gs->ship.pos.y)) {
    int i = 0, /* the ship is drawn in 3 rows */
        j = 0, /* the ship main body */
        k = 1; /* the ship middle part */
    for (i = 0; i < 3; i++) {
      /* Draw back part */
      Cell* ship_p1 = field_cell_at(gs, gs->ship.pos.x, gs->ship.pos.y - 1 + i);
      ship_p1->content = '-';
      ship_p1->text_color = FG_HI_YELLOW;
      ship_p1->background_color = BG_BLACK;

      Cell* ship_p2 =
          field_cell_at(gs, gs->ship.pos.x + 1, gs->ship.pos.y - 1 + i);
      ship_p2->content = '=';
      ship_p2->text_color = FG_HI_YELLOW;
      ship_p2->background_color = BG_BLACK;

      /* Draw the Gun part */
      if (i == 1) {
        k = 3;
        Cell* ship_p4 = field_cell_at(gs, gs->ship.pos.x + 5, gs->ship.pos.y);
        ship_p4->content = '>';
        ship_p4->text_color = FG_HI_YELLOW;
        ship_p4->background_color = BG_BLACK;
      } else {
        k = 1;
      }

      /* Draw ship main Body body*/
      for (j = 0; j < k; j++) {
        Cell* ship_p3 =
            field_cell_at(gs, gs->ship.pos.x + 2 + j, gs->ship.pos.y - 1 + i);
        ship_p3->content = ' ';
        ship_p3->text_color = FG_HI_WHITE;
        ship_p3->background_color = BG_HI_MAGENTA;
      } // end of body for
    }   // end of outer for loop
    /* If ther are powerups */
    if (gs->ship.powerup_time > 0) {
      Cell* ship_p5 = field_cell_at(gs, gs->ship.pos.x + 3, gs->ship.pos.y - 1);
      ship_p5->content = '>';
      ship_p5->text_color = FG_HI_YELLOW;
      ship_p5->background_color = BG_BLACK;

      Cell* ship_p6 = field_cell_at(gs, gs->ship.pos.x + 3, gs->ship.pos.y + 1);
      ship_p6->content = '>';
      ship_p6->text_color = FG_HI_YELLOW;
      ship_p6->background_color = BG_BLACK;
    }
  } // end of if
} // end of function draw_ship

/*++++++++++++++++++++++++++++++++++++++++++++++++*/
void draw_projectiles(GameState* gs) {
  Int2* proj_pos; // projectiles position

  /* Draw all projectiles*/
  for (int i = 0; i < vec_length(gs->projectiles); i++) {

    proj_pos = *vec_at(gs->projectiles, i); /* Projectile position */
    /* Draw projectiles only inside the field*/
    if (is_field_coordinate(gs, proj_pos->x, proj_pos->y)) {

      Cell* cell = field_cell_at(gs, proj_pos->x, proj_pos->y);
      cell->content = '>';
      cell->text_color = FG_RED;
      cell->background_color = BG_BLACK;
    } // end of if
  }   // end of for
} // end of function draw projectiles

/*++++++++++++++++++++++++++++++++++++++++++++++++*/
void draw_asteroids(GameState* gs) {
  Int2* astr_pos;
  /* Draw asteroids in the field */
  for (int i = 0; i < vec_length(gs->asteroids); i++) {

    astr_pos = *vec_at(gs->asteroids, i);

    /* Draw projectiles only inside the field*/
    if (is_field_coordinate(gs, astr_pos->x, astr_pos->y)) {

      Cell* cell = field_cell_at(gs, astr_pos->x, astr_pos->y);
      cell->content = ' ';
      cell->text_color = FG_WHITE;
      cell->background_color = BG_WHITE;
    } // end of if
  }   // end of for
} // end of function draw_asteroids

/*++++++++++++++++++++++++++++++++++++++++++++++++*/
void draw_powerups(GameState* gs) {
  Int2* powerups_pos;
  /* Draw powerups in the field */
  for (int i = 0; i < vec_length(gs->powerups); i++) {

    powerups_pos = *vec_at(gs->powerups, i);

    /* Draw powerups only inside the field*/
    if (is_field_coordinate(gs, powerups_pos->x, powerups_pos->y)) {

      Cell* cell = field_cell_at(gs, powerups_pos->x, powerups_pos->y);
      cell->content = '@';
      cell->text_color = FG_GREEN;
      cell->background_color = BG_BLACK;
    } // end of if
  }   // end of for
} // end of function draw_asteroids

/*++++++++++++++++++++++++++++++++++++++++++++++++++*/
void draw_explosions(GameState* gs) {
  /* */
  Explosion* exp;
  int zeichen;
  int i = 0;
  while (i < vec_length(gs->explosions)) {

    exp = *vec_at(gs->explosions, i);
    zeichen = -1;

    for (int j = 0; j < 2; j++) {
      /* Draw Horizontal */
      if (exp->age < 3) {
        if (is_field_coordinate(gs, exp->pos.x + (zeichen * 2 * (exp->age)),
                                exp->pos.y)) {
          Cell* cell1 = field_cell_at(
              gs, exp->pos.x + (zeichen * 2 * (exp->age)), exp->pos.y);
          cell1->content = '#';
          cell1->text_color = FG_YELLOW;
          cell1->background_color = BG_RED;
        }

        /* Draw Veritcal */
        if (is_field_coordinate(gs, exp->pos.x,
                                (exp->pos.y + zeichen * (exp->age)))) {
          Cell* cell2 = field_cell_at(gs, exp->pos.x,
                                      (exp->pos.y + zeichen * (exp->age)));
          cell2->content = '#';
          cell2->text_color = FG_YELLOW;
          cell2->background_color = BG_RED;
        } // end of coordinate comparison
      }   // end of age comparison
      zeichen = 1;
    } // end of for
    ++i;
  } // end of while
}

/*++++++++++++++++++++++++++++++++++++++++++++++++*/
bool handle_input(GameState* gs, char c) {
  /* Check input keys */
  switch (c) {
  case 'w': /* move up */
    if (gs->ship.pos.y > gs->field_begin.y + 1) {
      gs->ship.pos.y--;
    }
    break;
  case 's': /* move down */
    if (gs->ship.pos.y < (gs->field_end.y - 4)) {
      gs->ship.pos.y++;
    }
    break;
  case 'a': /* move left */
    if (gs->ship.pos.x > gs->field_begin.x) {
      gs->ship.pos.x--;
    }
    break;
  case 'd': /* move right */
    if (gs->ship.pos.x < (gs->field_end.x - 8)) {
      gs->ship.pos.x++;
    }
    break;
  }
  /* exit game if true */
  if (c == 'q') {
    return true;
  }

  /* Shoot projectiles check also if there are power ups */
  if (c == ' ') {
    /* if there are powerups consumed the ship shoots 3
     * projectiles. otherwise only one
     */
    int count = 1;
    int bull_y;
    int bull_x;
    if (gs->ship.powerup_time > 0) {
      count = 3;
    } // end of if

    for (int i = 0; i < count; i++) {
      switch (i) {
      case 0: /* Middle Projectile Shooter */
        bull_x = 0;
        bull_y = 0;
        break;
      case 1: /* Upper  Projectile Shooter */
        bull_x = -2;
        bull_y = -1;
        break;
      case 2: /* Lower Projectile Shooter */
        bull_x = -2;
        bull_y = 1;
        break;
      }
      Int2* proj = malloc(sizeof(Int2));
      if (proj == NULL){
        exit(1);
      }
      *proj = (Int2){.x = gs->ship.pos.x + 5 + bull_x,
                     .y = gs->ship.pos.y + bull_y};
      vec_push(gs->projectiles, proj);
    } // end of inner for
  } // end of outer for
  return false;
} // end of function hand_input

/*++++++++++++++++++++++++++++++++++++++++++++++++*/

bool collides_with_ship(Int2 ship_pos, Int2 pos) {
  /* Check if Ther is collision with the ship body */
  if (((ship_pos.x + 2 == pos.x) && (ship_pos.y - 1 == pos.y)) || /* upper */
      ((ship_pos.x + 2 == pos.x) && (ship_pos.y + 1 == pos.y)) || /* lower */
      ((ship_pos.x + 2 == pos.x) && (ship_pos.y + 0 == pos.y)) || /**********/
      ((ship_pos.x + 3 == pos.x) && (ship_pos.y + 0 == pos.y)) || /* Middle */
      ((ship_pos.x + 4 == pos.x) && (ship_pos.y + 0 == pos.y))) { /**********/
    return true;
  }
  return false;
} // end of function collides_with_ship

/*++++++++++++++++++++++++++++++++++++++++++++++++*/
void move_projectiles(GameState* gs) {
  Int2* bullets;
  int i = vec_length(gs->projectiles);
  while (i > 0) {
    --i;
    bullets = *vec_at(gs->projectiles, i);
    ++(bullets->x);

    if (bullets->x > gs->field_end.x) {
      vec_remove(gs->projectiles, i);
    } // end of if
  }   // end of while
} // end of function move_projectiles

/*++++++++++++++++++++++++++++++++++++++++++++++++*/
void move_asteroids(GameState* gs) {

  if (gs->time_step % 5 == 0) {
    Int2* astroid;
    int i = 0;
    while (i < vec_length(gs->asteroids)) {

      astroid = *vec_at(gs->asteroids, i);
      --(astroid->x);
      if (astroid->x < gs->field_begin.x - 1) {
        vec_remove(gs->asteroids, i);
      } // end of if
      ++i;
    } // end of while loop
  } // end of time_step comparison
} // end of function move_asteroids

/*++++++++++++++++++++++++++++++++++++++++++++++++*/
void move_powerups(GameState* gs) {
  Int2* pwr_ups;
  int i = 0;
  while (i < vec_length(gs->powerups)) {

    pwr_ups = *vec_at(gs->powerups, i);
    --(pwr_ups->x);
    if (pwr_ups->x < gs->field_begin.x - 1) {
      vec_remove(gs->powerups, i);
    } // end of if
    ++i;
  } // end of while
} // end of function move_powerups

/*++++++++++++++++++++++++++++++++++++++++++++++++*/
void move_explosions(GameState* gs) {
  /*  */
  Explosion* exp;
  int j = vec_length(gs->explosions);
  while (j > 0) {
    --j;
    exp = *vec_at(gs->explosions, j);
    exp->age++;
    if ((exp->age) > 5) {
      vec_remove(gs->explosions, j);
    }
  } // end of while
} // end of function move_explosions

/*++++++++++++++++++++++++++++++++++++++++++++++++*/
void spawn_asteroids(GameState* gs) {
  /* Astreroids are created every five time steps */
  if (gs->time_step % 5 == 0) {

    Int2* astr = malloc(sizeof(Int2));
      if (astr == NULL){
        exit(1);
      }
    *astr =
        (Int2){.x = gs->field_end.x - 2, .y = rand() % (gs->field_end.y - 1)};
    vec_push(gs->asteroids, astr);
  } // end of if
} // end of function spawn_asteroids

/*++++++++++++++++++++++++++++++++++++++++++++++++*/
void spawn_powerups(GameState* gs) {
  /* Powerups are created every fifty time steps */
  /* In every 200 Asteroids is one power up created */
  if ((gs->time_step + 1) % 1000 == 0) {
    Int2* pwr_ups = malloc(sizeof(Int2));
      if (pwr_ups == NULL){
        exit(1);
      }
    *pwr_ups = (Int2){.x = gs->field_end.x - 2,
                      .y = 1 + rand() % (gs->field_end.y - 3)};
    vec_push(gs->powerups, pwr_ups);
  } // end of if
} // end of function spawn_powerups

/*++++++++++++++++++++++++++++++++++++++++++++++++*/
void handle_projectile_asteroid_collisions(GameState* gs) {

  Int2* astr;
  Int2* proj;

  int i = 0;
  size_t len = vec_length(gs->projectiles);
  size_t len_astr = vec_length(gs->asteroids);
  int j = 0;

  while (j < len) {                  /* iterate through the projectiles */
    for (i = 0; i < len_astr; i++) { /* iterate through the asteroids*/
      if (len > 0) {

        proj = *vec_at(gs->projectiles, j);
        astr = *vec_at(gs->asteroids, i);

        if ((astr->x == proj->x) && (astr->y == proj->y)) {

          /* Save explosion status */
          Explosion* explosion_1 = malloc(sizeof(Explosion));
          explosion_1->pos.x = astr->x;
          explosion_1->pos.y = astr->y;
          explosion_1->age = -1;
          vec_push(gs->explosions, explosion_1);

          gs->points += 5;
          /* Remove collided Objects */
          vec_remove(gs->asteroids, i);
          vec_remove(gs->projectiles, j);
          /* After removal the iteration must start again*/
          j = 0;
          i = 0;
        } // end of if
      }

      len_astr = vec_length(gs->asteroids);
      len = vec_length(gs->projectiles);

    } // end of asteroid for
    j++;
  } // end of proj for
} // end of program

/*++++++++++++++++++++++++++++++++++++++++++++++++*/
void handle_powerup_ship_collisions(GameState* gs) {
  /* */
  Int2* pwr_ups;
  int i = vec_length(gs->powerups);
  while (i > 0) {
    --i;
    pwr_ups = *vec_at(gs->powerups, i);
    if (collides_with_ship(gs->ship.pos, *pwr_ups)) {
      vec_remove(gs->powerups, i);
      gs->ship.powerup_time = 1000;
      gs->points += 50;
    } // end of if
  }   // end of while
} // end of function

/*++++++++++++++++++++++++++++++++++++++++++++++++*/
void handle_asteroid_ship_collisions(GameState* gs) {
  Int2* astr;

  int i = vec_length(gs->asteroids);
  while (i > 0) {
    --i;
    astr = *vec_at(gs->asteroids, i);

    if (collides_with_ship(gs->ship.pos, *astr)) {
      /* Save explosion status */
      Explosion* explosion_1 = malloc(sizeof(Explosion));
      explosion_1->pos.x = astr->x;
      explosion_1->pos.y = astr->y;
      explosion_1->age = -1;
      vec_push(gs->explosions, explosion_1);

      vec_remove(gs->asteroids, i);
      --(gs->ship.health);
    } // end of if
  }   // end of while
} // end of function
