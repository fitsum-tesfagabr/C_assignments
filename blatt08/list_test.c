#include "../unity/unity.h"

#include "./list.h"

void setUp(void) {
}
void tearDown(void) {
}

void test_new_free(void) {
  List* l = list_new();
  TEST_ASSERT_EQUAL_INT(0, list_len(l));
  TEST_ASSERT_EQUAL(NULL, list_first(l));
  TEST_ASSERT_EQUAL(NULL, list_last(l));
  list_free(l);
}

void test_push_pop_back(void) {
  /* Some numbers whose addresses we're going to push in the list. */
  int i1 = 10;
  int i2 = 20;
  int i3 = 30;

  /* Create the list, push i1, i2, and i3, and check that list length is
   * increased. */
  List* l = list_new();
  TEST_ASSERT_EQUAL_INT(0, list_len(l));

  list_push_back(l, i1);
  TEST_ASSERT_EQUAL_INT(1, list_len(l));

  list_push_back(l, i2);
  TEST_ASSERT_EQUAL_INT(2, list_len(l));

  list_push_back(l, i3);
  TEST_ASSERT_EQUAL_INT(3, list_len(l));

  /* Walk through the list from first to last node and check that the nodes
   * exist and have the correct values.
   */
  {
    Node* n = list_first(l);
    TEST_ASSERT_NOT_EQUAL(NULL, n);
    TEST_ASSERT_EQUAL(i1, *node_val(n));

    n = node_next(n);
    TEST_ASSERT_NOT_EQUAL(NULL, n);
    TEST_ASSERT_EQUAL(i2, *node_val(n));

    n = node_next(n);
    TEST_ASSERT_NOT_EQUAL(NULL, n);
    TEST_ASSERT_EQUAL(i3, *node_val(n));

    n = node_next(n);
    TEST_ASSERT_EQUAL(NULL, n);
  }

  /* Walk through the list from last to first node and check that the nodes
   * exist and have the correct values.
   */
  {
    Node* n = list_last(l);
    TEST_ASSERT_NOT_EQUAL(NULL, n);
    TEST_ASSERT_EQUAL(i3, *node_val(n));

    n = node_prev(n);
    TEST_ASSERT_NOT_EQUAL(NULL, n);
    TEST_ASSERT_EQUAL(i2, *node_val(n));

    n = node_prev(n);
    TEST_ASSERT_NOT_EQUAL(NULL, n);
    TEST_ASSERT_EQUAL(i1, *node_val(n));

    n = node_prev(n);
    TEST_ASSERT_EQUAL(NULL, n);
  }

  /* Pop the list elements and check that they return the values of the popped
   * node and decrease the list size.
   */
  TEST_ASSERT_EQUAL_INT(i3, list_pop_back(l));
  TEST_ASSERT_EQUAL_INT(2, list_len(l));

  TEST_ASSERT_EQUAL_INT(i2, list_pop_back(l));
  TEST_ASSERT_EQUAL_INT(1, list_len(l));

  TEST_ASSERT_EQUAL_INT(i1, list_pop_back(l));
  TEST_ASSERT_EQUAL_INT(0, list_len(l));

  /* Free the list. */
  list_free(l);
}

/* Same as the previous test, but pushes/pops the elements at the front of the
 * list. */
void test_push_pop_front(void) {
  /* Some numbers whose addresses we're going to push in the list. */
  int i1 = 10;
  int i2 = 20;
  int i3 = 30;

  /* Create the list, push i1, i2, and i3, and check that list length is
   * increased. */
  List* l = list_new();
  TEST_ASSERT_EQUAL_INT(0, list_len(l));

  list_push_front(l, i1);
  TEST_ASSERT_EQUAL_INT(1, list_len(l));

  list_push_front(l, i2);
  TEST_ASSERT_EQUAL_INT(2, list_len(l));

  list_push_front(l, i3);
  TEST_ASSERT_EQUAL_INT(3, list_len(l));

  /* Walk through the list from first to last node and check that the nodes
   * exist and have the correct values.
   */
  {
    Node* n = list_first(l);
    TEST_ASSERT_NOT_EQUAL(NULL, n);
    TEST_ASSERT_EQUAL(i3, *node_val(n));

    n = node_next(n);
    TEST_ASSERT_NOT_EQUAL(NULL, n);
    TEST_ASSERT_EQUAL(i2, *node_val(n));

    n = node_next(n);
    TEST_ASSERT_NOT_EQUAL(NULL, n);
    TEST_ASSERT_EQUAL(i1, *node_val(n));

    n = node_next(n);
    TEST_ASSERT_EQUAL(NULL, n);
  }

  /* Walk through the list from last to first node and check that the nodes
   * exist and have the correct values.
   */
  {
    Node* n = list_last(l);
    TEST_ASSERT_NOT_EQUAL(NULL, n);
    TEST_ASSERT_EQUAL(i1, *node_val(n));

    n = node_prev(n);
    TEST_ASSERT_NOT_EQUAL(NULL, n);
    TEST_ASSERT_EQUAL(i2, *node_val(n));

    n = node_prev(n);
    TEST_ASSERT_NOT_EQUAL(NULL, n);
    TEST_ASSERT_EQUAL(i3, *node_val(n));

    n = node_prev(n);
    TEST_ASSERT_EQUAL(NULL, n);
  }

  /* Pop the list elements and check that they return the values of the popped
   * node and decrease the list size.
   */
  TEST_ASSERT_EQUAL_INT(i3, list_pop_front(l));
  TEST_ASSERT_EQUAL_INT(2, list_len(l));

  TEST_ASSERT_EQUAL_INT(i2, list_pop_front(l));
  TEST_ASSERT_EQUAL_INT(1, list_len(l));

  TEST_ASSERT_EQUAL_INT(i1, list_pop_front(l));
  TEST_ASSERT_EQUAL_INT(0, list_len(l));

  /* Free the list. */
  list_free(l);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_new_free);
  RUN_TEST(test_push_pop_back);
  RUN_TEST(test_push_pop_front);
  return UNITY_END();
}
