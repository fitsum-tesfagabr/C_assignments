#include "ctype.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define BUFSIZE 0x1000

/* read an entire text file into memory */
char* readfile(FILE* file) {
 
  char* buffer = malloc(1);
  buffer[0] = 0;
  size_t round = 0;
  if (file != NULL) {
    while (!feof(file)) {
      buffer = realloc(buffer, (round + 1) * BUFSIZE + 1);
      size_t nread =
          fread(buffer + round * BUFSIZE, sizeof(char), BUFSIZE, file);
      buffer[round * BUFSIZE + nread] = 0;
      round++;
    }
  }
 
  return buffer;
}

/* ********************************************************************************
 */
