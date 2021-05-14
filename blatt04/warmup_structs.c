#include "../unity/unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void setUp(void) {}
void tearDown(void) {}

int add_3(int i) { return i + 3; }

void add_assign_3(int *p) { *p += 3; }

struct Point {
  int x;
  int y;
};

struct Point add_point(struct Point p1, struct Point p2) {
  p1.x = p1.x + p2.x;
  p1.y = p1.y + p2.y;
  return p1;
}

void add_assign_point(struct Point *p1, struct Point p2) {
  p1->x = p1->x + p2.x;
  (*p1).y = (*p1).y + p2.y;
}

char *find_char(char c, char *s) {
  char *p; /* p points to the first occurance of 'c' in "s"*/
  for (int i = 0; i < strlen(s); i++) {
    if (c == s[i]) {
      p = &s[i];
      /* returns the address of the first occurance
       * of 'c' and terminates the function */
      return p;
    }
  }
  /* gets executed when there is no occurance of 'c' in "s" */
  return NULL;
}

void test_add_3_1(void) {
  int c = 'M';
  TEST_ASSERT_EQUAL('P', add_3(c));
}
void test_add_assign_3_1(void) {
  int c = 'A';
  add_assign_3(&c);
  TEST_ASSERT_EQUAL('D', c);
}

void test_add_point_1() {
  struct Point p1 = {1, 2};
  struct Point p2 = {10, 20};
  struct Point p3 = add_point(p1, p2);
  TEST_ASSERT_EQUAL(11, p3.x);
  TEST_ASSERT_EQUAL(22, p3.y);
}
void test_add_assign_point_1(void) {
  struct Point p1 = {35, 30};
  struct Point p2 = {20, 200};
  add_assign_point(&p1, p2);
  TEST_ASSERT_EQUAL(55, p1.x);
  TEST_ASSERT_EQUAL(230, p1.y);
}
void test_find_char_1(void) {
  char *s = "C Programming";
  TEST_ASSERT_EQUAL(s + 7, find_char('a', s));
  TEST_ASSERT_EQUAL(NULL, find_char('p', s));
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_add_3_1);
  RUN_TEST(test_add_assign_3_1);
  RUN_TEST(test_add_point_1);
  RUN_TEST(test_add_assign_point_1);
  RUN_TEST(test_find_char_1);
  return UNITY_END();
}
