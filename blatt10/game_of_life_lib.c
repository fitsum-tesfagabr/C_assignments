#include "./game_of_life_lib.h"
#include "../tui/tui.h"
#include "./bool_matrix.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
/*
 - Any live cell with fewer than two live neighbours dies, as if by
   underpopulation.
 - Any live cell with two or three live neighbours lives on to the
   next generation.
 - Any live cell with more than three live neighbours dies, as if
   by overpopulation.
 - Any dead cell with exactly three live neighbours becomes a
   live cell, as if by reproduction.
*/
bool inside_boundry(GameState* gs, int x, int y) {
  return x >= 0 && y >= 0 && x < gs->field_size.x && y < gs->field_size.y;
}
bool handle_input(GameState* gs, char c) {
  if (c == 'q') {
    return true;
  }
  Size2 size = (Size2){.x = gs->cursor_pos.x, .y = gs->cursor_pos.y};
  FILE* u_file;
  FILE* i_file;
  FILE* o_file;
  switch (c) {
  case 'w': /* move up */
    if (gs->cursor_pos.y > 0) {
      gs->cursor_pos.y--;
    }
    break;
  case 's': /* move down */
    if (gs->cursor_pos.y < gs->field_size.y - 1) {
      gs->cursor_pos.y++;
    }
    break;
  case 'a': /* move left */
    if (gs->cursor_pos.x > 0) {
      gs->cursor_pos.x--;
    }
    break;
  case 'd': /* move right */
    if (gs->cursor_pos.x < (gs->field_size.x - 1)) {
      gs->cursor_pos.x++;
    }
    break;
  case 'n': /* change state */
    if (*bool_matrix_at(gs->m_cur, size.x, size.y)) {
      *bool_matrix_at(gs->m_next, size.x, size.y) = false;

    } else {
      *bool_matrix_at(gs->m_next, size.x, size.y) = true;
    }
    break;
  case ' ':
    gs->simulation_active = !gs->simulation_active;
    break;
  case '-':
    ++gs->speed;
    break;
  case '+':
    if (gs->speed > 2) {
      --gs->speed;
    }
    break;
  case 'c':
    for (int i = 0; i < gs->field_size.x; i++) {
      for (int j = 0; j < gs->field_size.y; j++) {
        *bool_matrix_at(gs->m_next, i, j) = false;
      }
    }
    break;
  case 'u':
    u_file = fopen("save_u.gol", "w");
    write_to_file(gs, u_file);
    break;
  case 'i':
    i_file = fopen("save_i.gol", "w");
    write_to_file(gs, i_file);
    break;
  case 'o':
    o_file = fopen("save_o.gol", "w");
    write_to_file(gs, o_file);
    break;
  case 'U':
    u_file = fopen("save_u.gol", "r");
    read_from_file(gs, u_file);
    break;
  case 'I':
    i_file = fopen("save_i.gol", "r");
    read_from_file(gs, i_file);
    break;
  case 'O':
    o_file = fopen("save_o.gol", "r");
    read_from_file(gs, o_file);
    break;
  case 'v':
    gs->selection_active = !gs->selection_active;
    break;
  }

  return false;
}

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
void read_from_file(GameState* gs, FILE* file) {
  if (file != NULL) {
    /* First clear the screen */
    char* dimention = NULL;
    size_t len = 0;
    size_t read = 0;
    char wc[5] = {'\0'};
    char hc[5] = {'\0'};
    int i = 0;
    read = getline(&dimention, &len, file);

    bool comma = false;

    for (int k = 0; k < read; k++) {
      if (dimention[k] == ',') {
        comma = true;
        i = 0;
        wc[k] = '\0';
        continue;
      }
      if (comma) {

        hc[i] = dimention[k];
        i++;
      } else {
        wc[i] = dimention[k];
        i++;
      }
    }
    /*clear screan */
    for (int i = 0; i < gs->field_size.y; i++) {
      for (int j = 0; j < gs->field_size.x; j++) {
        *bool_matrix_at(gs->m_next, j, i) = false;
        *bool_matrix_at(gs->m_cur, j, i) = false;
      }
    }
    /* Draw from file */
    char c;
    int wid = MIN(atoi(wc), gs->field_size.x);
    int hei = MIN(atoi(hc), gs->field_size.y);
    int diff = atoi(wc) - gs->field_size.x;
    for (int i = 0; i < hei; i++) {
      for (int j = 0; j < wid; j++) {
        c = fgetc(file);
        if (c == '.') {
          *bool_matrix_at(gs->m_next, j, i) = false;
          // move_cursor_to(j, i);
          // printf("f");
        } else if (c == '#') {
          *bool_matrix_at(gs->m_next, j, i) = true;
          // move_cursor_to(j, i);
          // printf("t");
        } else if (c == '\n') {
          // move_cursor_to(j, i);
          // printf("n");
          j--;
        }
      }
      int k = 0;
      while (k <= diff) {
        fgetc(file);
        // move_cursor_to(0, i);
        // printf("o");
        if (k > 100) {
          exit(42);
        }
        ++k;
      }
    }
    /* wrap up */
    if (dimention != NULL) {
      free(dimention);
    }
  }
  if (file != NULL) {

    fclose(file);
  }
}

void write_to_file(GameState* gs, FILE* file) {
  if (file != NULL) {
    fprintf(file, "%ld,%ld\n", gs->field_size.x, gs->field_size.y);
    for (int i = 0; i < gs->field_size.y; i++) {
      for (int j = 0; j < gs->field_size.x; j++) {
        if (*bool_matrix_at(gs->m_cur, j, i)) {
          fputc('#', file);
        } else {
          fputc('.', file);
        }
      }
      if (!(i >= gs->field_size.y - 1)) {
        fputc('\n', file);
      }
    }
    fclose(file);
  }
}
void print_cell(GameState* gs, Size2 size, const char c) {
  char* bg_color = BG_BLACK;
  char* fg_color = FG_WHITE;
  if (size.x == gs->cursor_pos.x && size.y == gs->cursor_pos.y) {
    bg_color = BG_WHITE;
    fg_color = FG_BLACK;
  }
  Cell* cell = tui_cell_at(size.x, size.y);
  cell->content = c;
  cell->text_color = fg_color;
  cell->background_color = bg_color;
}

void print_cursor(GameState* gs, Size2 size) {
  Cell* cell = tui_cell_at(size.x, size.y);
  cell->content = ' ';
  cell->text_color = FG_BLACK;
  cell->background_color = BG_WHITE;
}

bool cells_eq(BoolMatrix* c1, BoolMatrix* c2, int x, int y) {
  return *bool_matrix_at(c1, x, y) == *bool_matrix_at(c2, x, y);
}

void update(GameState* gs) {
  if (gs->time_step % gs->speed == 0) {
    for (int i = 0; i < gs->field_size.x; i++) {
      for (int j = 0; j < gs->field_size.y; j++) {
        if (!cells_eq(gs->m_cur, gs->m_next, i, j)) {
          *bool_matrix_at(gs->m_cur, i, j) = *bool_matrix_at(gs->m_next, i, j);
        }
      }
    }
  }
}

void draw(GameState* gs) {
  /*
   - Any live cell with fewer than two live neighbours dies, as if by
     underpopulation.
   - Any live cell with two or three live neighbours lives on to the
     next generation.
   - Any live cell with more than three live neighbours dies, as if
     by overpopulation.
   - Any dead cell with exactly three live neighbours becomes a
     live cell, as if by reproduction.
  */
  Size2 size = (Size2){.x = gs->cursor_pos.x, .y = gs->cursor_pos.y};
  print_cursor(gs, size);
  /* calculate evolution if active */
  if (gs->simulation_active) {
    int count_live_neighbours = 0;
    for (int i = 0; i < gs->field_size.x; i++) {
      for (int j = 0; j < gs->field_size.y; j++) {
        /* cell is alive */
        count_live_neighbours = count_live_cells(gs, i, j);

        if (*bool_matrix_at(gs->m_cur, i, j)) {
          if (count_live_neighbours < 2) {
            *bool_matrix_at(gs->m_next, i, j) = false;
          } else if (count_live_neighbours >= 2 && count_live_neighbours <= 3) {
            *bool_matrix_at(gs->m_next, i, j) = true;
          } else {
            *bool_matrix_at(gs->m_next, i, j) = false;
          }
        } else { /* cell is dead */
          if (count_live_neighbours == 3) {
            *bool_matrix_at(gs->m_next, i, j) = true;
          }
        }
      }
    }
  }
  print_cells(gs);
}

int count_live_cells(GameState* gs, int x, int y) {
  int count_live_neighbours = 0;
  int boundry_x = 0;
  int boundry_y = 0;
  for (int col = -1; col < 2; col++) {
    for (int row = -1; row < 2; row++) {
      if (row == 0 && col == 0) {
        continue;
      }
      boundry_x = x + col;
      boundry_y = y + row;
      if (boundry_x < 0) {
        boundry_x = gs->field_size.x - 1;
      } else if (boundry_x == gs->field_size.x) {
        boundry_x = 0;
      }
      if (boundry_y < 0) {
        boundry_y = gs->field_size.y - 1;
      } else if (boundry_y == gs->field_size.y) {
        boundry_y = 0;
      }

      if (x == 0 && y == 0 && boundry_x > gs->field_size.x) {
        move_cursor_to(5, 5);
        printf("%d %d %ld", boundry_x, boundry_y, gs->field_size.x);
        exit(42);
      }

      if (*bool_matrix_at(gs->m_cur, boundry_x, boundry_y)) {
        ++count_live_neighbours;
      }
    }
  }
  return count_live_neighbours;
}

void print_cells(GameState* gs) {
  Size2 size;
  for (int i = 0; i < gs->field_size.x; i++) {
    for (int j = 0; j < gs->field_size.y; j++) {
      size.x = i;
      size.y = j;
      if (!*bool_matrix_at(gs->m_next, i, j)) {
        print_cell(gs, size, ' ');
      } else {
        print_cell(gs, size, '#');
      }
    }
  }
}
