#include "../unity/unity.h"

#include "./game_highscores.h"
#include "./json_data.h"
#include "./json_printer.h"
#include "./json_reader.h"
#include "./reader.h"
#include "./memtools.h"
void setUp(void) {
}
void tearDown(void) {
}

void test_highscore_to_json(void) {
  Highscore highscore = (Highscore){
      .name = "foo",
      .points = 112,
      .distance = 308,
  };
  printf("\n");
  JsonValue* jval = highscore_to_json(&highscore);
  json_fprint_value(stdout, 0, jval);

  highscore = (Highscore){
      .name = "bar",
      .points = 23232,
      .distance = 190308,
  };

  printf("\n");
  JsonValue* jval2 = highscore_to_json(&highscore);
  json_fprint_value(stdout, 0, jval2);

  printf("\n");
  if (jval != NULL) {
    json_value_free(jval);
  }
  if (jval2 != NULL) {
    json_value_free(jval2);
  }
}
void test_json_to_highscores(void) {
  
  /* Four sample Scores are saved as a json value
   * representation. The JsonValue will then be
   * converted to Highscore in the function
   * json_to_Highscores(JsonValue* val)*/
  Highscore highscore1 = (Highscore){
      .name = "bar",
      .points = 65,
      .distance = 308,
  };
  Highscore highscore2 = (Highscore){
      .name = "foo",
      .points = 55,
      .distance = 198,
  };

  Highscore highscore3 = (Highscore){
      .name = "xxx",
      .points = 23,
      .distance = 1308,
  };
  Highscore highscore4 = (Highscore){
      .name = "AAA",
      .points = 22,
      .distance = 1889,
  };

  /* Convert first highscore to json */
  JsonValue* jval1 = highscore_to_json(&highscore1);
  JsonValue* jval2 = highscore_to_json(&highscore2);
  JsonValue* jval3 = highscore_to_json(&highscore3);
  JsonValue* jval4 = highscore_to_json(&highscore4);
  
  Vec* mems = vec_new();
  /* Each Highscore info is represented as a unique member with its rank */
  JsonMember* mem1 = json_member_new(strcpy_malloc("0"), jval1); /* #1 */
  JsonMember* mem2 = json_member_new(strcpy_malloc("1"), jval2); /* #2 */
  JsonMember* mem3 = json_member_new(strcpy_malloc("2"), jval3); /* #3 */
  JsonMember* mem4 = json_member_new(strcpy_malloc("3"), jval4); /* #4 */
  
  vec_push(mems, mem1);
  vec_push(mems, mem2);
  vec_push(mems, mem3);
  vec_push(mems, mem4);

  /* Collect all members in one Object*/
  JsonObject* jobj = json_object_new(mems);

  /* Represent the object of members as a value */
  JsonValue* val = json_value_new_object(jobj);
  
  /* This is a short demonistration how the memebers are saved in the json
   * format 
   */
  json_fprint_object(stdout, 0, jobj);
  
  /***************************TEST***************************************/
  /* Test if the function json_to_highscores return the Highscrores collected in
   * vec */
  Vec* mem_r = json_to_highscores(val);
  /* The total Scores are four */
  TEST_ASSERT_EQUAL_size_t(4, vec_length(mem_r));
  
  /* Top scorer is "bar" */
  Highscore* h = *vec_at(mem_r, 0);
  TEST_ASSERT_EQUAL_STRING("bar", h->name);
  /* Second top scorer points = 55 */
  h = *vec_at(mem_r, 1);
  TEST_ASSERT_EQUAL_INT(55, h->points);
  /* Third top scorer distance = 1308 */
  h = *vec_at(mem_r, 2);
  TEST_ASSERT_EQUAL_INT(1308, h->distance);
  /* The fourth top scorer is "AAA" with total points = 22 and distance = 1889 */
  h = *vec_at(mem_r, 3);
  TEST_ASSERT_EQUAL_STRING("AAA", h->name);
  TEST_ASSERT_EQUAL_INT(22, h->points);
  TEST_ASSERT_EQUAL_INT(1889, h->distance);

  printf("\n");
  
  /* Free all the allocated memories */
  if (val != NULL) {
    json_value_free(val);
  }
  if (mem_r != NULL){
    for(int i = 0; i < vec_length(mem_r); i++){
      h = *vec_at(mem_r, i);
      free(h->name); 
      free(*vec_at(mem_r, i));
    }
    vec_free(mem_r);
  }
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_highscore_to_json);
  RUN_TEST(test_json_to_highscores);
  return UNITY_END();
}
