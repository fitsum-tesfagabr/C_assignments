#include "fib_lib.h"
#include <stdio.h>

int main(void) {
  int n;
  printf("Input: ");
  scanf("%d", &n);
  printf("fib(%d) = %d\n", n, fib_slow(n));
}
