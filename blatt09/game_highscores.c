#include <stdlib.h>
#include <string.h>

#include "./game_highscores.h"
#include "./vec.h"
#include "./json_reader.h"
#include "./json_printer.h"
#include "./memtools.h"
#include "./reader.h"

#define HIGHSCORE_PATH "highscores.json"

void highscores_free(Vec* highscores) {
  for (size_t i = 0; i < vec_length(highscores); ++i) {
    Highscore* hs = *vec_at(highscores, i);
    free(hs->name);
    free(hs);
  }
  vec_free(highscores);
}

JsonValue* uri_to_json(const char* uri) {
  char command[255];
  sprintf(command, "curl -X GET %s 2>/dev/null", uri);

  FILE* curl_output_file = popen(command, "r");
  char* curl_output = readfile(curl_output_file);
  fclose(curl_output_file);

  reader* r = make_reader(curl_output);
  JsonValue* json = parse_json(r);
  free(r);
  free(curl_output);

  return json;
}
/* `popen` runs a command in the shell and returns the commands stdout file. */

JsonValue* download_highscore_json(void) {
  return uri_to_json("https://stream.inpro.informatik.uni-freiburg.de/highscores");
}

JsonValue* download_highscore_json_for(char* name) {
  char uri[255];
  sprintf(uri, "https://stream.inpro.informatik.uni-freiburg.de/highscores/%s", name);
  return uri_to_json(uri);
}

void upload_highscore_json(JsonValue* highscore) {
  /* Write highscore to a temporary json file. */
  FILE* tmp_file = fopen("tmp_highscore.json", "w");
  json_fprint_value(tmp_file, 0, highscore);
  fclose(tmp_file);

  /* Send the json file to the highscore server via a HTTP POST request. */
  const char* command =
    "curl -X POST -H 'Content-Type: application/json' "
    "-d @tmp_highscore.json "
    "https://stream.inpro.informatik.uni-freiburg.de/highscores "
    "2>&1";
  FILE* curl_output = popen(command, "r");
  fclose(curl_output);

  /* Delete the temporary file. */
  remove("tmp_highscore.json");
}

Vec* json_to_highscores(JsonValue* highscores_json) {
  /* TODO */
  return NULL;
}

JsonValue* highscore_to_json(Highscore* highscore) {
  /* TODO */
  return NULL;
}
