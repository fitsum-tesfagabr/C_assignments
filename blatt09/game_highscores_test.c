#include "../tui/ansi_codes.h"
#include "../unity/unity.h"
#include "./game_highscores.h"
#include "./json_data.h"
#include "./json_printer.h"
#include "./json_reader.h"
#include "./memtools.h"
#include "./reader.h"
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

  /* Collect and represent all members in one Object*/
  JsonObject* jobj = json_object_new(mems);

  /* Represent the object of members as a value */
  JsonValue* val = json_value_new_object(jobj);

  /* This is a short demonistration how the memebers are saved in the json
   * format
   */
  printf("\n");
  fprintf(stdout, FG_BLACK BG_YELLOW
          "Json Data to be converted to Highscores" COLOR_RESET "\n");

  json_fprint_object(stdout, 0, jobj);

  /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
  /***************************TEST*********************************************/

  /* Test if the function json_to_highscores return the Highscrores collected in
   * vec */
  { // TEST_BLOCK start

    Highscore* h = NULL;
    Vec* mem_r = json_to_highscores(val);
    /* The total Scores are four */
    TEST_ASSERT_EQUAL_size_t(4, vec_length(mem_r));

    /* Top scorer is "bar" */
    h = *vec_at(mem_r, 0);
    TEST_ASSERT_EQUAL_STRING("bar", h->name);
    TEST_ASSERT_EQUAL_INT(65, h->points);
    TEST_ASSERT_EQUAL_INT(308, h->distance);

    /* Second top scorer is "foo" */
    h = *vec_at(mem_r, 1);
    TEST_ASSERT_EQUAL_STRING("foo", h->name);
    TEST_ASSERT_EQUAL_INT(55, h->points);
    TEST_ASSERT_EQUAL_INT(198, h->distance);

    /* Third top scorer is "xxx" */
    h = *vec_at(mem_r, 2);
    TEST_ASSERT_EQUAL_STRING("xxx", h->name);
    TEST_ASSERT_EQUAL_INT(23, h->points);
    TEST_ASSERT_EQUAL_INT(1308, h->distance);

    /* The fourth top scorer is "AAA" */
    h = *vec_at(mem_r, 3);
    TEST_ASSERT_EQUAL_STRING("AAA", h->name);
    TEST_ASSERT_EQUAL_INT(22, h->points);
    TEST_ASSERT_EQUAL_INT(1889, h->distance);

    printf("\n");

    /* Free all the allocated memories */
    if (val != NULL) {
      json_value_free(val);
    }
    if (mem_r != NULL) {
      highscores_free(mem_r);
    } // end of if
  }   // TEST_BLOCK end
} // end of method

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_highscore_to_json);
  RUN_TEST(test_json_to_highscores);
  return UNITY_END();
}
