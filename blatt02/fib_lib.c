#include "fib_lib.h"

// calculate nth fibonacci-number recursively
int fib_slow(int n) {
  if (n == 0) {
    return 0;
  } else if (n == 1) {
    return 1;
  } else {
    return fib_slow(n - 1) + fib_slow(n - 2);
  }
}

// quicker method to calculate nth fibonacci number
int fib_fast(int n) {
  if (n == 0) {
    return 0;
  } else if (n == 1) {
    return 1;
  } else {

    int cache[n + 1];
    cache[0] = 0;
    cache[1] = 1;

    for (int i = 2; i < n + 1; i++) {
      cache[i] = cache[i - 1] + cache[i - 2];
    } // end for
    return cache[n];
  } // end else
} // end fib_fast
