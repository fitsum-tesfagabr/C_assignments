#ifndef MENU_H
#define MENU_H
#include <stdlib.h>
#include <string.h>

#include "./json_data.h"
#include "./json_printer.h"
#include "./json_reader.h"
#include "./memtools.h"
#include "./mini_sweeper_lib.h"
#include "./reader.h"
#include "./vec.h"

typedef enum MenuList { SETTINGS, HIGHSCORES, MAIN } menu_list;

typedef struct Menu_status {
  int menu_str_size[4];
  int settings_str_size[3];
  char* highlight_color[4];
  int menu_cursor_pos_y;
  menu_list which_section;
} Menu_status;

void draw_menu(GameState* gs, Menu_status* st);
void highlight_menu_cursor(Menu_status* st);
void select_menu(GameState* gs, Menu_status* st);
void settings(GameState* gs, Menu_status* st);
void display_highscores(GameState* gs, Menu_status* st);
void main_menu(GameState* gs, Menu_status* st);
bool handle_menu_input(GameState* gs, Menu_status* st, char c);
JsonValue* file_to_json(const char* file_name);
void upload_highscore_json(JsonValue* highscore);
Vec* json_to_highscores(JsonValue* highscores_json);
JsonValue* highscore_to_json(H_score* highscore);
void remove_file(char* file_name);
void highscores_menu(GameState* gs, Menu_status* st);
void json_to_file(JsonValue* h_json, FILE* file);
JsonValue* convert_highscores_vec_to_value(GameState* gs);
#endif
