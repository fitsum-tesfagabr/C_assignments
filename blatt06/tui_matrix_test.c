#include "../unity/unity.h"
#include "./ansi_codes.h"
#include "./tui_matrix.h"
#include <string.h>

void setUp(void) {
}
void tearDown(void) {
}

void test_cell_eq(void) {
  Cell c1 = (Cell){
      .content = '.', .text_color = FG_WHITE, .background_color = BG_BLACK};
  Cell c2 = (Cell){
      .content = '.', .text_color = FG_WHITE, .background_color = BG_BLACK};
  TEST_ASSERT_EQUAL_INT(1, cell_eq(&c1, &c2));
  c2.text_color = FG_BLUE;
  TEST_ASSERT_EQUAL_INT(0, cell_eq(&c1, &c2));
}

void test_matrix_new(void) {
  Cell c1 = (Cell){
      .content = '*', .text_color = FG_GREEN, .background_color = BG_WHITE};
  Matrix* m = matrix_new(11, 13, &c1);
  TEST_ASSERT_EQUAL_size_t(11, matrix_width(m));
  TEST_ASSERT_EQUAL_size_t(13, matrix_height(m));
  /* Since all the cells are intialized to same values
   * any random cell must fulfill the initialized
   * characteristics
   * */
  for (int i = 1; i <= matrix_height(m); i++) {
    for (int j = 1; j <= matrix_width(m); j++) {
      TEST_ASSERT_EQUAL_CHAR('*', matrix_cell_at(m, j, i)->content);
      TEST_ASSERT_EQUAL_STRING(FG_GREEN, matrix_cell_at(m, j, i)->text_color);
      TEST_ASSERT_EQUAL_STRING(BG_WHITE,
                               matrix_cell_at(m, j, i)->background_color);
    }
  }
  matrix_free(m);
}
void test_matrix_clear_with(void) {

  Cell c1 = (Cell){
      .content = 'f', .text_color = FG_GREEN, .background_color = BG_WHITE};
  Matrix* m = matrix_new(11, 13, &c1);

  c1.content = '.';
  c1.text_color = FG_YELLOW;
  c1.background_color = BG_MAGENTA;

  matrix_clear_with(m, &c1);

  for (int i = 1; i <= matrix_height(m); i++) {
    for (int j = 1; j <= matrix_width(m); j++) {

      TEST_ASSERT_EQUAL_CHAR('.', matrix_cell_at(m, j, i)->content);
      TEST_ASSERT_EQUAL_STRING(FG_YELLOW, matrix_cell_at(m, j, i)->text_color);
      TEST_ASSERT_EQUAL_STRING(BG_MAGENTA,
                               matrix_cell_at(m, j, i)->background_color);
    }
  }
  matrix_free(m);
}
void test_matrix_clear(void) {
  Cell c1 = (Cell){
      .content = '#', .text_color = FG_GREEN, .background_color = BG_WHITE};
  Matrix* m = matrix_new(20, 20, &c1);

  matrix_clear(m);

  for (int i = 1; i <= matrix_height(m); i++) {
    for (int j = 1; j <= matrix_width(m); j++) {

      TEST_ASSERT_EQUAL_CHAR(' ', matrix_cell_at(m, j, i)->content);
      TEST_ASSERT_EQUAL_STRING(FG_WHITE, matrix_cell_at(m, j, i)->text_color);
      TEST_ASSERT_EQUAL_STRING(BG_BLACK,
                               matrix_cell_at(m, j, i)->background_color);
    }
  }
  matrix_free(m);
}
void test_matrix_width(void) {
  Cell c1 = (Cell){
      .content = 'o', .text_color = FG_CYAN, .background_color = BG_BLACK};
  Matrix* m = matrix_new(20, 20, &c1);
  TEST_ASSERT_EQUAL_size_t(20, matrix_width(m));
  matrix_resize(m, 5, 7, &c1);
  TEST_ASSERT_EQUAL_size_t(5, matrix_width(m));
  matrix_resize(m, 10, 13, &c1);
  TEST_ASSERT_EQUAL_size_t(10, matrix_width(m));
  matrix_free(m);
}
void test_matrix_height(void) {
  Cell c1 = (Cell){
      .content = '#', .text_color = FG_GREEN, .background_color = BG_WHITE};
  Matrix* m = matrix_new(20, 20, &c1);
  TEST_ASSERT_EQUAL_size_t(20, matrix_height(m));
  matrix_resize(m, 5, 7, &c1);
  TEST_ASSERT_EQUAL_size_t(7, matrix_height(m));
  matrix_resize(m, 10, 13, &c1);
  TEST_ASSERT_EQUAL_size_t(13, matrix_height(m));
  matrix_free(m);
}
void test_matrix_cell_at(void) {
  Cell c1 = (Cell){
      .content = '#', .text_color = FG_YELLOW, .background_color = BG_BLUE};
  Matrix* m = matrix_new(20, 20, &c1);
  /* default value */

  TEST_ASSERT_EQUAL_CHAR('#', matrix_cell_at(m, 3, 4)->content);
  TEST_ASSERT_EQUAL_STRING(FG_YELLOW, matrix_cell_at(m, 3, 5)->text_color);
  TEST_ASSERT_EQUAL_STRING(BG_BLUE, matrix_cell_at(m, 3, 5)->background_color);

  matrix_cell_at(m, 3, 5)->content = 'f';
  matrix_cell_at(m, 3, 5)->text_color = FG_RED;
  matrix_cell_at(m, 3, 5)->background_color = BG_WHITE;
  /* After cell (3,5) replaced with different properties*/
  TEST_ASSERT_EQUAL_CHAR('f', matrix_cell_at(m, 3, 5)->content);
  TEST_ASSERT_EQUAL_STRING(FG_RED, matrix_cell_at(m, 3, 5)->text_color);
  TEST_ASSERT_EQUAL_STRING(BG_WHITE, matrix_cell_at(m, 3, 5)->background_color);

  matrix_cell_at(m, 5, 5)->content = 'o';
  matrix_cell_at(m, 5, 5)->text_color = FG_GREEN;
  matrix_cell_at(m, 5, 5)->background_color = BG_WHITE;

  /* After cell (5,5) replaced with different properties*/
  TEST_ASSERT_EQUAL_CHAR('o', matrix_cell_at(m, 5, 5)->content);
  TEST_ASSERT_EQUAL_STRING(FG_GREEN, matrix_cell_at(m, 5, 5)->text_color);
  TEST_ASSERT_EQUAL_STRING(BG_WHITE, matrix_cell_at(m, 5, 5)->background_color);
  matrix_free(m);
}
void test_matrix_set_str_at(void) {
  Cell c1 = (Cell){
      .content = '.', .text_color = FG_YELLOW, .background_color = BG_BLUE};
  Matrix* m = matrix_new(30, 30, &c1);
  char* s = "MATRIX!";
  matrix_set_str_at(m, 31, 31, s, FG_BLUE, BG_MAGENTA);

  for (int j = 1; j <= matrix_height(m); j++) {
    for (int i = 1; i <= matrix_width(m); i++) {
      TEST_ASSERT_EQUAL_CHAR('.', matrix_cell_at(m, i, j)->content);
      TEST_ASSERT_EQUAL_STRING(FG_YELLOW, matrix_cell_at(m, i, j)->text_color);
      TEST_ASSERT_EQUAL_STRING(BG_BLUE,
                               matrix_cell_at(m, i, j)->background_color);
    }
  }

  matrix_set_str_at(m, 6, 8, s, FG_BLUE, BG_MAGENTA);

  for (int j = 1; j <= matrix_height(m); j++) {
    for (int i = 1; i <= matrix_width(m); i++) {
      /* check if the row starting from 'x' to 'strlen(s)' is replaced by
       * the given string.
       * */
      if (j == 8 && (i >= 6 && i <= 6 + strlen(s) - 1)) {
        TEST_ASSERT_EQUAL_CHAR(s[i - 6], matrix_cell_at(m, i, j)->content);
        TEST_ASSERT_EQUAL_STRING(FG_BLUE, matrix_cell_at(m, i, j)->text_color);
        TEST_ASSERT_EQUAL_STRING(BG_MAGENTA,
                                 matrix_cell_at(m, i, j)->background_color);
        continue;
      }

      TEST_ASSERT_EQUAL_CHAR('.', matrix_cell_at(m, i, j)->content);
      TEST_ASSERT_EQUAL_STRING(FG_YELLOW, matrix_cell_at(m, i, j)->text_color);
      TEST_ASSERT_EQUAL_STRING(BG_BLUE,
                               matrix_cell_at(m, i, j)->background_color);
    }
  }
  matrix_set_str_at(m, 10, 27, s, FG_BLUE, BG_MAGENTA);
  /* If the string does not fit in the row only the string elements
   * that fit in the row are added.
   *
   * Therefore, in this case, only the first 4 characters will be
   * added.
   * */
  TEST_ASSERT_EQUAL_CHAR('R', matrix_cell_at(m, 13, 27)->content);
  TEST_ASSERT_EQUAL_STRING(FG_BLUE, matrix_cell_at(m, 13, 27)->text_color);
  TEST_ASSERT_EQUAL_STRING(BG_MAGENTA,
                           matrix_cell_at(m, 13, 27)->background_color);
  matrix_free(m);
}
void test_matrix_resize(void) {
  Cell c1 = (Cell){
      .content = '+', .text_color = FG_YELLOW, .background_color = BG_BLUE};
  Matrix* m = matrix_new(2, 2, &c1);

  matrix_resize(m, 5, 7, &c1);
  /* Resize to a smaller dimension than the original
   * Then except the dimensions nothing changes.
   * The properties of the cells remain unchanged.
   * */
  TEST_ASSERT_EQUAL_size_t(5, matrix_width(m));
  TEST_ASSERT_EQUAL_size_t(7, matrix_height(m));

  TEST_ASSERT_EQUAL_CHAR('+', matrix_cell_at(m, 5, 7)->content);
  TEST_ASSERT_EQUAL_STRING(FG_YELLOW, matrix_cell_at(m, 5, 7)->text_color);
  TEST_ASSERT_EQUAL_STRING(BG_BLUE, matrix_cell_at(m, 5, 7)->background_color);

  /* Resize to a new size larger in width or height or both.
   * The newly created cells will inherite the properties of
   * the passed Cell parameters.
   * */
  c1.content = '#';
  c1.text_color = FG_RED;
  c1.background_color = BG_YELLOW;
  matrix_resize(m, 6, 8, &c1);
  /* The previous defined Cell remain untouched
   */
  TEST_ASSERT_EQUAL_size_t(6, matrix_width(m));
  TEST_ASSERT_EQUAL_size_t(8, matrix_height(m));

  TEST_ASSERT_EQUAL_CHAR('+', matrix_cell_at(m, 5, 7)->content);
  TEST_ASSERT_EQUAL_STRING(FG_YELLOW, matrix_cell_at(m, 5, 7)->text_color);
  TEST_ASSERT_EQUAL_STRING(BG_BLUE, matrix_cell_at(m, 5, 7)->background_color);

  /* The newly created Cells inherite the property of the passed
   * cell properties.
   */
  TEST_ASSERT_EQUAL_CHAR('#', matrix_cell_at(m, 5, 8)->content);
  TEST_ASSERT_EQUAL_STRING(FG_RED, matrix_cell_at(m, 5, 8)->text_color);
  TEST_ASSERT_EQUAL_STRING(BG_YELLOW,
                           matrix_cell_at(m, 5, 8)->background_color);
  matrix_free(m);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_cell_eq);
  RUN_TEST(test_matrix_new);
  RUN_TEST(test_matrix_clear_with);
  RUN_TEST(test_matrix_clear);
  RUN_TEST(test_matrix_width);
  RUN_TEST(test_matrix_height);
  RUN_TEST(test_matrix_cell_at);
  RUN_TEST(test_matrix_set_str_at);
  RUN_TEST(test_matrix_resize);
  return UNITY_END();
}
