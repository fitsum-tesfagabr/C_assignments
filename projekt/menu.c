#include "./menu.h"
#include "../tui/tui.h"
#include "./mini_sweeper_lib.h"
#include "./vec.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void draw_menu(GameState* gs, Menu_status* st) {
  switch (st->which_section) {
  case MAIN:
    main_menu(gs, st);
    break;
  case SETTINGS:
    settings(gs, st);
    break;
  case HIGHSCORES:
    display_highscores(gs, st);
    break;
  }
}

void main_menu(GameState* gs, Menu_status* st) {

  char buf[5][255];
  char shortcut[5][255];

  for (int i = 0; i < 4; i++) {
    st->highlight_color[i] = FG_WHITE;
  }

  highlight_menu_cursor(st);

  sprintf(buf[0], "MINESWEEPER");
  tui_set_str_at(1, 1, buf[0], FG_HI_CYAN, BG_BLACK);

  sprintf(buf[1], "NEW GAME");
  tui_set_str_at(3, 2, buf[1], st->highlight_color[0], BG_BLACK);

  sprintf(buf[2], "SETTINGS");
  tui_set_str_at(3, 3, buf[2], st->highlight_color[1], BG_BLACK);

  sprintf(buf[3], "HIGHSCORES");
  tui_set_str_at(3, 4, buf[3], st->highlight_color[2], BG_BLACK);

  sprintf(buf[4], "EXIT");
  tui_set_str_at(3, 5, buf[4], st->highlight_color[3], BG_BLACK);

  sprintf(shortcut[0], "SHORTCUTS");
  tui_set_str_at(1, 7, shortcut[0], FG_YELLOW, BG_BLACK);

  sprintf(shortcut[1], "  Q      EXIT GAME");
  tui_set_str_at(1, 8, shortcut[1], FG_WHITE, BG_BLACK);

  sprintf(shortcut[2], "  W      PREVIOUS ITEM");
  tui_set_str_at(1, 9, shortcut[2], FG_WHITE, BG_BLACK);

  sprintf(shortcut[3], "  S      NEXT ITEM");
  tui_set_str_at(1, 10, shortcut[3], FG_WHITE, BG_BLACK);

  sprintf(shortcut[4], "  SPACE  ACTIVATE ITEM");
  tui_set_str_at(1, 11, shortcut[4], FG_WHITE, BG_BLACK);
}

void highlight_menu_cursor(Menu_status* st) {
  st->highlight_color[st->menu_cursor_pos_y - 2] = FG_CYAN;
}

void select_menu(GameState* gs, Menu_status* st) {
  if (gs->mode == MENU) {
    switch (st->menu_cursor_pos_y - 2) {
    case 0:
      gs->mode = PLAY;
      gs->endgame_info = "";
      gs->cursor_pos = (Int2){.x = 2, .y = 2};
      gs->play_time = 1;
      gs->start_time = time(0);
      draw_new_game(gs);
      break;
    case 1:
      st->menu_cursor_pos_y = 2;
      st->which_section = SETTINGS;
      settings(gs, st);
      break;
    case 2:
      st->menu_cursor_pos_y = 2;
      st->which_section = HIGHSCORES;
      display_highscores(gs, st);
      break;
    case 3:
      exit_safely(gs);
      exit(1);
      break;
    }
  }
}

bool handle_menu_input(GameState* gs, Menu_status* st, char c) {
  int limit = 0;
  switch (c) {
  case 'q':
    if (st->which_section == MAIN) {
      return true;
    }
    if (st->which_section == SETTINGS) {

      FILE* fp = fopen("settings.tsv", "w");
      if (fp == NULL) {
        exit(1);
      }
      write_settings(gs, fp);
      fclose(fp);
    }
    st->menu_cursor_pos_y = 2;
    st->which_section = MAIN;
    break;
  case 'w':
    if (st->menu_cursor_pos_y > 2) {
      st->menu_cursor_pos_y--;
    }
    break;
  case 's':
    if (st->which_section == MAIN) {
      limit = 5;
    } else {
      limit = 4;
    }
    if (st->menu_cursor_pos_y < limit) {
      st->menu_cursor_pos_y++;
    }
    break;
  case 'a':
    if (st->which_section == SETTINGS) {
      switch (st->menu_cursor_pos_y - 2) {
      case 0:
        if (gs->play_field_width > 5) {
          gs->play_field_width--;
        }
        break;
      case 1:
        if (gs->play_field_height > 5) {
          gs->play_field_height--;
        }
        break;
      case 2:
        if (gs->probability > 0.01) {
          gs->probability -= 0.01;
        }
        break;
      }
    }
    break;
  case 'd':
    if (st->which_section == SETTINGS) {
      switch (st->menu_cursor_pos_y - 2) {
      case 0:
        if (gs->play_field_width < 50) {
          gs->play_field_width++;
        }
        break;
      case 1:
        if (gs->play_field_height < 17) {
          gs->play_field_height++;
        }
        break;
      case 2:
        if (gs->probability < 0.99) {
          gs->probability += 0.01;
        }
        break;
      }
    }
    break;
  case ' ':
    if (st->which_section == MAIN) {
      select_menu(gs, st);
    }
    break;
  }
  return false;
}

void settings_menu(GameState* gs, Menu_status* st) {

  char buf[4][255];
  char shortcut[6][255];

  for (int i = 0; i < 3; i++) {
    st->highlight_color[i] = FG_WHITE;
  }

  highlight_menu_cursor(st);

  sprintf(buf[0], "OPTIONS");
  tui_set_str_at(1, 1, buf[0], FG_HI_CYAN, BG_BLACK);

  sprintf(buf[1], "WIDTH        %ld", gs->play_field_width);
  tui_set_str_at(3, 2, buf[1], st->highlight_color[0], BG_BLACK);

  sprintf(buf[2], "HEIGHT       %ld", gs->play_field_height);
  tui_set_str_at(3, 3, buf[2], st->highlight_color[1], BG_BLACK);

  sprintf(buf[3], "PROBABILITY  %.2f", gs->probability);
  tui_set_str_at(3, 4, buf[3], st->highlight_color[2], BG_BLACK);

  sprintf(shortcut[0], "SHORTCUTS");
  tui_set_str_at(1, 7, shortcut[0], FG_YELLOW, BG_BLACK);

  sprintf(shortcut[1], "  Q   GO BACK");
  tui_set_str_at(1, 8, shortcut[1], FG_WHITE, BG_BLACK);

  sprintf(shortcut[2], "  W   PREVIOUS ITEM");
  tui_set_str_at(1, 9, shortcut[2], FG_WHITE, BG_BLACK);

  sprintf(shortcut[3], "  S   NEXT ITEM");
  tui_set_str_at(1, 10, shortcut[3], FG_WHITE, BG_BLACK);

  sprintf(shortcut[4], "  A   DECREASE SELECTED ITEM");
  tui_set_str_at(1, 11, shortcut[4], FG_WHITE, BG_BLACK);

  sprintf(shortcut[5], "  D   INCREASE SELECTED ITEM");
  tui_set_str_at(1, 12, shortcut[5], FG_WHITE, BG_BLACK);
}

void settings(GameState* gs, Menu_status* st) {
  settings_menu(gs, st);
}

void highscores_menu(GameState* gs, Menu_status* st) {

  char buf[12][255];

  sprintf(buf[0], "TOP 10 HIGHSCORES");
  tui_set_str_at(1, 1, buf[0], FG_HI_YELLOW, BG_BLACK);

  sprintf(buf[1], "POINTS   TIME   WIDTH   HEIGHT   PROBABILITY");
  tui_set_str_at(3, 3, buf[1], FG_WHITE, BG_BLACK);

  char* file_name = "highscores.json";
  if (vec_length(gs->highscores) > 0) {
    JsonValue* json = file_to_json(file_name);
    if (json != NULL) {
      Vec* h_scores = json_to_highscores(json);
      for (int i = 0; i < vec_length(h_scores); i++) {

        H_score* h = *vec_at(h_scores, i);
        /* display points */
        sprintf(buf[2 + i], "%6d%7d%8d%9d%14.2f\t", h->points, h->play_time,
                h->width, h->height, h->probability);
        tui_set_str_at(3, 4 + i, buf[2 + i], FG_HI_WHITE, BG_BLACK);
      }
      vec_free(h_scores);
    }
    json_value_free(json);
  }
}

void display_highscores(GameState* gs, Menu_status* st) {
  highscores_menu(gs, st);
}
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
JsonValue* file_to_json(const char* file_name) {
  FILE* file_output = fopen(file_name, "r");
  if (!file_output) {
    return NULL;
  }
  char* file_output_buff = readfile(file_output);
  fclose(file_output);

  reader* r = make_reader(file_output_buff);
  JsonValue* json = parse_json(r);
  free(r);
  free(file_output_buff);
  return json;
}

void json_to_file(JsonValue* json, FILE* file) {
  json_fprint_value(file, 0, json);
}

Vec* json_to_highscores(JsonValue* highscores_json) {
  /* Array of scores are stored as a vector */
  Vec* scores = vec_new();

  /* According to the format of json the value type of highscores is Object */
  if (json_value_type(highscores_json) == JSON_OBJECT) {
    /* Members are saved in vector form */
    Vec* mem = json_object_members(json_value_as_object(highscores_json));

    for (int i = 0; i < vec_length(mem); i++) {
      /* For each Highscore info we need to save memory in heap
       * like: { "0": {...},
       *         "1": {...}
       *         ...
       *       }
       */
      H_score* hs = malloc_or_exit(sizeof(H_score));

      /* Read each value of the memebers coupled with rank */
      JsonMember* member = *vec_at(mem, i);
      JsonObject* val = json_value_as_object(json_member_value(member));

      /* Finde members of Highscore with the help of function
       * declared in json_data.h
       */
      JsonValue* points = json_object_find(val, "points");
      hs->points = json_value_as_number(points);

      JsonValue* width = json_object_find(val, "width");
      hs->width = json_value_as_number(width);

      JsonValue* height = json_object_find(val, "height");
      hs->height = json_value_as_number(height);

      JsonValue* probability = json_object_find(val, "probability");
      hs->probability = json_value_as_number(probability);

      JsonValue* play_time = json_object_find(val, "play_time");
      hs->play_time = json_value_as_number(play_time);
      /* Add up each highscore to the vector 'scores' */
      vec_push(scores, hs);
    }
    /* Return Highscore vector if successfull */
    return scores;
  }
  /* Return NULL if json format is wrong */
  return NULL;
}

JsonValue* highscore_to_json(H_score* highscore) {
  /* Allocate memory for member keys of highscore */
  char* name1 = strcpy_malloc("points");
  char* name2 = strcpy_malloc("width");
  char* name3 = strcpy_malloc("height");
  char* name4 = strcpy_malloc("probability");
  char* name5 = strcpy_malloc("play_time");

  /* Change Highscore values to json value */
  JsonValue* points = json_value_new_number(highscore->points);
  JsonValue* width = json_value_new_number(highscore->width);
  JsonValue* height = json_value_new_number(highscore->height);
  JsonValue* probability = json_value_new_number(highscore->probability);
  JsonValue* play_time = json_value_new_number(highscore->play_time);

  /* Add Highscores with their respective keys */
  JsonMember* memb1 = json_member_new(name1, points);
  JsonMember* memb2 = json_member_new(name2, width);
  JsonMember* memb3 = json_member_new(name3, height);
  JsonMember* memb4 = json_member_new(name4, probability);
  JsonMember* memb5 = json_member_new(name5, play_time);

  /* Insert all the memeber in a vector */
  Vec* members = vec_new();
  vec_push(members, memb1);
  vec_push(members, memb2);
  vec_push(members, memb3);
  vec_push(members, memb4);
  vec_push(members, memb5);

  /* Collect the member vector to an object */
  JsonObject* score_res = json_object_new(members);

  /* Return the object as a json value */
  JsonValue* all = json_value_new_object(score_res);
  return all;
}

JsonValue* convert_highscores_vec_to_value(GameState* gs) {
  vec_sort(gs->highscores);
  Vec* members = vec_new();
  JsonMember* memb[10];
  char rank[10][100];
  for (int i = 0; i < vec_length(gs->highscores); i++) {
    sprintf(rank[i], "%d", i);
    H_score* hs = *vec_at(gs->highscores, i);
    memb[i] = json_member_new(strcpy_malloc(rank[i]), highscore_to_json(hs));
    vec_push(members, memb[i]);
  }
  JsonObject* score_res = json_object_new(members);
  JsonValue* all = json_value_new_object(score_res);
  return all;
}

void remove_file(char* file_name) {
  remove(file_name);
}
