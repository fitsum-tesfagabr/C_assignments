#ifndef GAME_HIGHSCORES_H
#define GAME_HIGHSCORES_H

#include "./json_data.h"
#include "./game_lib.h"

typedef struct Highscore {
  char* name;
  int points;
  int distance;
} Highscore;

void highscores_free(Vec* highscores);

JsonValue* uri_to_json(const char* uri);
JsonValue* download_highscore_json(void);
JsonValue* download_highscore_json_for(char* name);
void upload_highscore_json(JsonValue* highscore);

Vec* json_to_highscores(JsonValue* highscores_json);
JsonValue* highscore_to_json(Highscore* highscore);

#endif /* GAME_HIGHSCORES_H */
