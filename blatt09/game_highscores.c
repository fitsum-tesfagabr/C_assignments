#include <stdlib.h>
#include <string.h>

#include "./game_highscores.h"
#include "./json_printer.h"
#include "./json_reader.h"
#include "./memtools.h"
#include "./reader.h"
#include "./vec.h"

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
  pclose(curl_output_file);

  reader* r = make_reader(curl_output);
  JsonValue* json = parse_json(r);
  free(r);
  free(curl_output);

  return json;
}
/* `popen` runs a command in the shell and returns the commands stdout file. */

JsonValue* download_highscore_json(void) {
  return uri_to_json(
      "https://stream.inpro.informatik.uni-freiburg.de/highscores");
}

JsonValue* download_highscore_json_for(char* name) {
  char uri[255];
  sprintf(uri, "https://stream.inpro.informatik.uni-freiburg.de/highscores/%s",
          name);
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
  pclose(curl_output);

  /* Delete the temporary file. */
  remove("tmp_highscore.json");
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
      Highscore* hs = malloc_or_exit(sizeof(Highscore));

      /* Read each value of the memebers coupled with rank */
      JsonMember* member = *vec_at(mem, i);
      JsonObject* val = json_value_as_object(json_member_value(member));

      /* Finde members of Highscore with the help of function
       * declared in json_data.h
       */
      JsonValue* name = json_object_find(val, "name");
      hs->name = strcpy_malloc(json_value_as_string(name));

      JsonValue* points = json_object_find(val, "points");
      hs->points = json_value_as_number(points);

      JsonValue* distance = json_object_find(val, "distance");
      hs->distance = json_value_as_number(distance);

      /* Add up each highscore to the vector 'scores' */
      vec_push(scores, hs);
    }
    /* Return Highscore vector if successfull */
    return scores;
  }
  /* Return NULL if json format is wrong */
  return NULL;
}

JsonValue* highscore_to_json(Highscore* highscore) {
  /* Allocate memory for member keys of highscore */
  char* name1 = strcpy_malloc("name");
  char* name2 = strcpy_malloc("points");
  char* name3 = strcpy_malloc("distance");
  char* name4 = strcpy_malloc(highscore->name);

  /* Change Highscore values to json value */
  JsonValue* name = json_value_new_string(name4);
  JsonValue* points = json_value_new_number(highscore->points);
  JsonValue* distance = json_value_new_number(highscore->distance);

  /* Add Highscores with their respective keys */
  JsonMember* memb1 = json_member_new(name1, name);
  JsonMember* memb2 = json_member_new(name2, points);
  JsonMember* memb3 = json_member_new(name3, distance);

  /* Insert all the memeber in a vector */
  Vec* members = vec_new();
  vec_push(members, memb1);
  vec_push(members, memb2);
  vec_push(members, memb3);

  /* Collect the member vector to an object */
  JsonObject* score_res = json_object_new(members);

  /* Return the object as a json value */
  JsonValue* all = json_value_new_object(score_res);
  return all;
}
