#include "./game_of_life_lib.h"
#include "../tui/tui.h"
#include "./bool_matrix.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
bool done = false;
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
}// end of inside_boundry

bool handle_input(GameState* gs, char c) {
  if (c == 'q') {
    return true;
  }//end of if
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
    //gs->selection_active = false;
    for (int i = 0; i < gs->field_size.x; i++) {
      for (int j = 0; j < gs->field_size.y; j++) {
        *bool_matrix_at(gs->m_next, i, j) = false;
      }
    }
    break;
  case 'u':
    done = true;
    u_file = fopen("save_u.gol", "w");
    write_to_file(gs, u_file);
    break;
  case 'i':
    done = true;
    i_file = fopen("save_i.gol", "w");
    write_to_file(gs, i_file);
    break;
  case 'o':
    done = true;
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
    done = false;
    gs->selection_active = !gs->selection_active;
    gs->selection_start = (Size2){.x = gs->cursor_pos.x, .y = gs->cursor_pos.y};
    break;
  }// end of switch
  return false;
}// end of function handle_input

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
      }// end of if
      if (comma) {
        hc[i] = dimention[k];
        i++;
      } else {
        wc[i] = dimention[k];
        i++;
      }// end of else
    }// end of for loop
    int start_x = 0;
    int start_y = 0;
    char c;
    /*clear screan */
    if(gs->selection_active){
        start_x = gs->cursor_pos.x;
        start_y = gs->cursor_pos.y;
    }// end of if
   if(!gs->selection_active){ 
    for (int i = 0; i < gs->field_size.y; i++) {
      for (int j = 0; j < gs->field_size.x; j++) {
        *bool_matrix_at(gs->m_next, j, i) = false;
        *bool_matrix_at(gs->m_cur, j, i) = false;
      }// end of for internal
    }// end of for external
  }// end of if 
    int wid = MIN(atoi(wc), gs->field_size.x);
    int hei = MIN(atoi(hc), gs->field_size.y);
    wid = wid + start_x > gs->field_size.x ? gs->field_size.x: wid + start_x;
    hei = hei + start_y > gs->field_size.y ? gs->field_size.y: hei + start_y;
    int diff = start_x +  atoi(wc) - gs->field_size.x;
    /* Draw from file */
    for (int i = start_y; i < hei; i++) {
      for (int j = start_x; j < wid; j++) {
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
        }// end of else if
      }// end of for internal
      int k = 0;
      while (k <= diff) {
        fgetc(file);
        // move_cursor_to(0, i);
        // printf("o");
        if (k > 100) {
          exit(42);
        }
        ++k;
      }// end of while
    }// end of external for loop
    /* wrap up */
    if (dimention != NULL) {
      free(dimention);
    }
  }// end of if that checks fiel if NULL
  if (file != NULL) {
    fclose(file);
  }
}// end of read_from_file

void write_to_file(GameState* gs, FILE* file) {
  size_t width = gs->field_size.x;
  size_t height = gs->field_size.y;

  int end_x = gs->field_size.x;
  int end_y = gs->field_size.y;
  
  int start_x = 0;
  int start_y = 0;

  if(gs->selection_active){
      start_x = gs->selection_start.x;
      start_y = gs->selection_start.y;
      end_x = gs->cursor_pos.x + 1;
      end_y = gs->cursor_pos.y + 1;
      width = abs(gs->selection_start.x - gs->cursor_pos.x) + 1;
      height = abs(gs->selection_start.y - gs->cursor_pos.y) + 1;
  }// end of if

  if (file != NULL) {
    
    fprintf(file, "%ld,%ld\n", width, height);

    for (int i = start_y; i < end_y; i++) {
      for (int j = start_x; j < end_x; j++) {
        if (*bool_matrix_at(gs->m_cur, j, i)) {
          fputc('#', file);
        } else {
          fputc('.', file);
        }
      }// end of for internal
      if (!(i >= gs->field_size.y - 1)) {
        fputc('\n', file);
      }
    }// end of for external
    fclose(file);
  }// end of if to check file if NULL
}// end of write_to_file

bool inside_selection(GameState* gs, Size2 size){
  if(gs->selection_active){
  if(
     ((size.x >= gs->selection_start.x && size.x <= gs->cursor_pos.x) && 
     (size.y >= gs->selection_start.y && size.y <= gs->cursor_pos.y))
      ){
        return true;
  }
  
  }// end of if
  return false;
  }// end of inside_selection

void print_cell(GameState* gs, Size2 size, const char c) {
  char* bg_color = BG_BLACK;
  char* fg_color = FG_WHITE;
  if ((inside_selection(gs, size) && !done) || (size.x == gs->cursor_pos.x && size.y == gs->cursor_pos.y)) {
    bg_color = BG_WHITE;
    fg_color = FG_BLACK;
  }
  Cell* cell = tui_cell_at(size.x, size.y);
  cell->content = c;
  cell->text_color = fg_color;
  cell->background_color = bg_color;
}// end of print_cell

void print_cursor(GameState* gs, Size2 size) {
  Cell* cell = tui_cell_at(size.x, size.y);
  cell->content = ' ';
  cell->text_color = FG_BLACK;
  cell->background_color = BG_WHITE;
}// end of print cursor

bool cells_eq(BoolMatrix* c1, BoolMatrix* c2, int x, int y) {
  return *bool_matrix_at(c1, x, y) == *bool_matrix_at(c2, x, y);
}// end of cells_eq

void update(GameState* gs) {
  if (gs->time_step % gs->speed == 0) {
    for (int i = 0; i < gs->field_size.x; i++) {
      for (int j = 0; j < gs->field_size.y; j++) {
        if (!cells_eq(gs->m_cur, gs->m_next, i, j)) {
          *bool_matrix_at(gs->m_cur, i, j) = *bool_matrix_at(gs->m_next, i, j);
        }// end of if
      }// end of for internal
    }// end of for external
  }// end of if
}// end of update

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
}// end fo draw

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
}// end of count_live_cells

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
}// end of print cells
