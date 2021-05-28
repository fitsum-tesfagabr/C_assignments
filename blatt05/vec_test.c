#include "../unity/unity.h"
#include "./vec.h"
#include <stdbool.h>

void setUp(void) {}
void tearDown(void) {}

void test_vec_at(void) {
  Vec *xs = vec_new();
  for (int i = 0; i < 20; i++) {
    vec_push(xs, i);
  }
  /* Test if the elements are inserted correctly */
  TEST_ASSERT_EQUAL_INT(2, *vec_at(xs, 2));
  TEST_ASSERT_EQUAL_INT(19, *vec_at(xs, 19));
  vec_free(xs);
}

void test_vec_lenght(void) {
  Vec *xs = vec_new();
  /* Since no elements are inserted yet, the length must be '0'
   * and the length must be resized with the inserted or removed
   * elements
   */
  TEST_ASSERT_EQUAL_INT(0, vec_length(xs));
  for (int i = 0; i < 5; i++) {
    vec_push(xs, i);
  }

  TEST_ASSERT_EQUAL_INT(5, vec_length(xs));
  /* Remove the last element two times */
  vec_pop(xs);
  vec_pop(xs);
  TEST_ASSERT_EQUAL_INT(3, vec_length(xs));
  vec_free(xs);
}

void test_vec_capacity(void) {
  Vec *xs = vec_new();
  /* after struct intialization, the capacity must be 1 */
  TEST_ASSERT_EQUAL_INT(1, vec_capacity(xs));
  for (int i = 0; i < 4; i++) {
    vec_push(xs, i);
  }
  /* for 4 elements the capacity is expected to be 4*/
  TEST_ASSERT_EQUAL_INT(4, vec_capacity(xs));
  vec_push(xs, -1);

  /* the capacity will be doubled if it is not enough, or will be
   * halfed if it is more than or equal to double the number of
   * elements stored
   */
  TEST_ASSERT_EQUAL_INT(8, vec_capacity(xs));
  for (int i = 0; i < 3; i++) {
    vec_pop(xs);
  }
  TEST_ASSERT_EQUAL_INT(2, vec_capacity(xs));
  vec_free(xs);
}

void test_vec_new(void) {
  Vec *xs = vec_new();
  /* The function vec_new() intializes the struct pointer with
   * length = 0 and a capacity of 1, if correctly set.
   */
  if (xs != NULL) {
    TEST_ASSERT_EQUAL_INT(0, vec_length(xs));
    TEST_ASSERT_EQUAL_INT(1, vec_capacity(xs));
  }
  vec_free(xs);
}

void test_vec_push(void) {
  Vec *xs = NULL;
  /* it is possible to insert an element if the struct pointer is
   * initialized correctly. Therfore, the function 'vec_push'
   * returns true if successful, else false.
   * It is necessary also that the capacity and length are updated
   * correctly.
   */
  TEST_ASSERT_EQUAL_INT(false, vec_push(xs, 1));

  xs = vec_new(); /* Initialize the sturct pointer */
  vec_push(xs, 10);
  TEST_ASSERT_EQUAL_INT(10, *vec_at(xs, 0));
  vec_push(xs, 1);
  vec_push(xs, 0);
  TEST_ASSERT_EQUAL_INT(3, vec_length(xs));
  TEST_ASSERT_EQUAL_INT(4, vec_capacity(xs));

  TEST_ASSERT_EQUAL_INT(true, vec_push(xs, 1));
  vec_free(xs);
}

void test_vec_pop(void) {
  /* The function vec_pop does the reverse of vec_push, but it does not
   * return anything except removing the last element and updating
   * lenght and capacity.
   */
  Vec *xs = vec_new();
  vec_pop(xs); /* do nothing as long as there are no elements inserted yet */
  TEST_ASSERT_EQUAL_INT(0, vec_length(xs));
  TEST_ASSERT_EQUAL_INT(1, vec_capacity(xs));

  for (int i = 0; i < 10; i++) {
    vec_push(xs, -i);
  }

  TEST_ASSERT_EQUAL_INT(-9, *vec_at(xs, 9));
  TEST_ASSERT_EQUAL_INT(10, vec_length(xs));
  vec_pop(xs);

  TEST_ASSERT_EQUAL_PTR(NULL, vec_at(xs, 9)); /* last element is removed */
  TEST_ASSERT_EQUAL_INT(-8, *vec_at(xs, 8));
  TEST_ASSERT_EQUAL_INT(9, vec_length(xs)); /* length reduced by one */
  vec_free(xs);
}

void test_vec_swap_int(void) {
  Vec *xs = vec_new();
  vec_push(xs, 1);
  vec_push(xs, -7);
  /* before swapping */
  TEST_ASSERT_EQUAL_INT(1, *vec_at(xs, 0));
  TEST_ASSERT_EQUAL_INT(-7, *vec_at(xs, 1));

  swap_int(vec_at(xs, 0), vec_at(xs, 1));
  /* after swapping */
  TEST_ASSERT_EQUAL_INT(-7, *vec_at(xs, 0));
  TEST_ASSERT_EQUAL_INT(1, *vec_at(xs, 1));
  vec_free(xs);
}

void test_vec_min_between(void) {
  Vec *xs = vec_new();
  vec_push(xs, 1);
  vec_push(xs, -5);
  vec_push(xs, 0);
  vec_push(xs, 23);
  vec_push(xs, 12);
  vec_push(xs, -1);
  /* Return smalles element for the give range if valid, else return
   * value is NULL
   */
  TEST_ASSERT_EQUAL_INT(-5, *vec_min_between(xs, 0, 5));
  TEST_ASSERT_EQUAL_INT(-1, *vec_min_between(xs, 2, 5));
  TEST_ASSERT_EQUAL_INT(0, *vec_min_between(xs, 2, 4));

  TEST_ASSERT_EQUAL_PTR(NULL, vec_min_between(xs, -2, 4)); /* -2 is invalid */
  TEST_ASSERT_EQUAL_PTR(NULL, vec_min_between(xs, 4, 2));  /* from > to */
  TEST_ASSERT_EQUAL_PTR(NULL, vec_min_between(xs, 2, 7));  /* 7 out of range */
  vec_free(xs);
}

void test_vec_sort(void) {
  Vec *xs = vec_new();
  vec_push(xs, 1);
  vec_push(xs, -5);
  vec_push(xs, 0);
  vec_push(xs, 23);
  vec_push(xs, 12);
  vec_push(xs, -1);
  /* before sort */
  TEST_ASSERT_EQUAL_INT(1, *vec_at(xs, 0));
  TEST_ASSERT_EQUAL_INT(-5, *vec_at(xs, 1));
  TEST_ASSERT_EQUAL_INT(0, *vec_at(xs, 2));
  TEST_ASSERT_EQUAL_INT(23, *vec_at(xs, 3));
  TEST_ASSERT_EQUAL_INT(12, *vec_at(xs, 4));
  TEST_ASSERT_EQUAL_INT(-1, *vec_at(xs, 5));
  vec_sort(xs);
  /* after sort*/
  TEST_ASSERT_EQUAL_INT(-5, *vec_at(xs, 0));
  TEST_ASSERT_EQUAL_INT(-1, *vec_at(xs, 1));
  TEST_ASSERT_EQUAL_INT(0, *vec_at(xs, 2));
  TEST_ASSERT_EQUAL_INT(1, *vec_at(xs, 3));
  TEST_ASSERT_EQUAL_INT(12, *vec_at(xs, 4));
  TEST_ASSERT_EQUAL_INT(23, *vec_at(xs, 5));
  vec_free(xs);
}
void test_vec_free(void) {
  Vec *xs = vec_new();
  vec_free(xs);
  /* After the dynamically allocated memory is cleared
   * xs refers to nothing, threfore, NULL.
   */
  TEST_ASSERT_EQUAL_PTR(NULL, xs);
}

/* This is not actual test but, it prints out in a desired format */
void test_vec_print(void) {
  Vec *xs = vec_new();
  vec_print(xs);
  for (size_t i = 0; i < 5; ++i) {
    vec_push(xs, -i * 2);
    /* the inserted elements will be sorted before get printed */
    vec_sort(xs);
    vec_print(xs);
  }
  for (size_t i = 0; i < 5; ++i) {
    vec_pop(xs);
    vec_print(xs);
  }
  vec_free(xs);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_vec_at);
  RUN_TEST(test_vec_lenght);
  RUN_TEST(test_vec_capacity);
  RUN_TEST(test_vec_new);
  RUN_TEST(test_vec_push);
  RUN_TEST(test_vec_pop);
  RUN_TEST(test_vec_swap_int);
  RUN_TEST(test_vec_min_between);
  RUN_TEST(test_vec_sort);
  RUN_TEST(test_vec_print);

  return UNITY_END();
}
