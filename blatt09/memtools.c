#include <string.h>

#include "./memtools.h"

void* malloc_or_exit(size_t num_bytes) {
  void* p = malloc(num_bytes);
  if (p == NULL) {
    exit(1);
  }
  return p;
}

char* strcpy_malloc(char* s) {
  char* copy = malloc_or_exit((strlen(s) + 1) * sizeof(char));
  strcpy(copy, s);
  return copy;
}
