#include "../unity/unity.h"
#include "./fib_lib.h"

void setUp(void) {}

void tearDown(void) {}

void test_fib_slow_15(void) { TEST_ASSERT_EQUAL(610, fib_slow(15)); }

void test_fib_slow_0(void) { TEST_ASSERT_EQUAL(0, fib_slow(0)); }

void test_fib_slow_1(void) { TEST_ASSERT_EQUAL(1, fib_slow(1)); }

void test_fib_fast_0(void) { TEST_ASSERT_EQUAL(0, fib_fast(0)); }
void test_fib_fast_1(void) { TEST_ASSERT_EQUAL(1, fib_fast(1)); }
void test_fib_fast_35(void) { TEST_ASSERT_EQUAL(9227465, fib_fast(35)); }
int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_fib_slow_0);
  RUN_TEST(test_fib_slow_1);
  RUN_TEST(test_fib_slow_15);

  RUN_TEST(test_fib_fast_0);
  RUN_TEST(test_fib_fast_1);
  RUN_TEST(test_fib_fast_35);
  return UNITY_END();
}
