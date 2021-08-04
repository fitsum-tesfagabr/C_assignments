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

/* Menu modes */
typedef enum MenuList { SETTINGS, HIGHSCORES, MAIN } menu_list;

/* Data structure for MENU */
typedef struct Menu_status {
  int menu_str_size[4];
  int settings_str_size[3];
  char* highlight_color[4];
  int menu_cursor_pos_y;
  menu_list which_section;
} Menu_status;

/* Display Menu to terminal */
void draw_menu(GameState* gs, Menu_status* st);

/* Highlight the current menu fields */
void highlight_menu_cursor(Menu_status* st);

/* Take necessary action based on selected menu. Ex. For NEW GAME - open
 * newgame, SETTINGS - manipulate game settings, HIGHSCORE - display first 10
 * high scores */
void select_menu(GameState* gs, Menu_status* st);

/* Manipulate Game settings. */
void settings(GameState* gs, Menu_status* st);

/* Display First 10 Highscores if exit */
void display_highscores(GameState* gs, Menu_status* st);

/* Display MAIN MENU. */
void main_menu(GameState* gs, Menu_status* st);

/* Handle menu selections */
bool handle_menu_input(GameState* gs, Menu_status* st, char c);

/* Convert File to json. */
JsonValue* file_to_json(const char* file_name);

/*
void upload_highscore_json(JsonValue* highscore);
*/

/* Convert json format to highscore datastructure */
Vec* json_to_highscores(JsonValue* highscores_json);

/* Convert Highscore datastructure to json format */
JsonValue* highscore_to_json(H_score* highscore);

/* Remove file if exist */
void remove_file(char* file_name);

/* Display Highscore Info to terminal. */
void highscores_menu(GameState* gs, Menu_status* st);

/* Save json format to file in disc. */
void json_to_file(JsonValue* h_json, FILE* file);

/* Convert Highscore vectors to json format  */
JsonValue* convert_highscores_vec_to_value(GameState* gs);
#endif
