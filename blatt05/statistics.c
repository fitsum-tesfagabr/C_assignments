#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "./vec.h"

#define SUCCESS 0
#define ERROR_NO_FURTHER_INPUT -1
#define ERROR_STRING_IS_NOT_A_NUMBER -2

int read_int(int *user_input) {
  char *line = NULL;
  size_t line_len = 0;
  ssize_t status = getline(&line, &line_len, stdin);
  if (status < 0) {
    free(line);
    return ERROR_NO_FURTHER_INPUT;
  }
  errno = 0;
  char *end = NULL;
  int i = strtol(line, &end, 10);
  free(line);
  if (errno != 0 || end == line) {
    return ERROR_STRING_IS_NOT_A_NUMBER;
  } else {
    *user_input = i;
    return SUCCESS;
  }
}
