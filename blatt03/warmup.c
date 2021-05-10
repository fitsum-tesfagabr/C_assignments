#include "../unity/unity.h"
#include <string.h>

void setUp(void) {}

void tearDown(void) {}

int my_strlen(char *s) { return strlen(s); }

int my_strcmp(char *s1, char *s2) {
  if (strcmp(s1, s2) == 0) {
    return 0;
  } else {
    return 1;
  }
}

void test_my_strlen_1(void) {
  TEST_ASSERT_EQUAL(12, my_strlen("Hello World!"));
}

void test_my_strlen_2(void) {
  TEST_ASSERT_EQUAL(13, my_strlen("C Programming"));
}

void test_my_strcmp_1(void) {
  TEST_ASSERT_EQUAL(1, my_strcmp("Hello World!", "Hello world!"));
}

void test_my_strcmp_2(void) {
  TEST_ASSERT_EQUAL(0, my_strcmp("C Programming", "C Programming"));
}

int main(int argc, char *argv[]) {
  UNITY_BEGIN();
  RUN_TEST(test_my_strlen_1);
  RUN_TEST(test_my_strlen_2);
  RUN_TEST(test_my_strcmp_1);
  RUN_TEST(test_my_strcmp_2);
  return UNITY_END();
}
