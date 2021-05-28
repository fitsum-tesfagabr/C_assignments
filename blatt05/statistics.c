#include "../unity/unity.h"
#include "./vec.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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

void statistics() {
  Vec *xs = vec_new();
  int user_input;          /*stores user input*/
  int end_reading = false; /* indicates end of reading */
  int invalid = 0;         /* counts invalid inputs */
  /* The loop iterates till CTRL + D is pressed */
  while (true) {
    switch (read_int(&user_input)) {
    case 0:
      /* if a valid number is inserted, it will be stored */
      vec_push(xs, user_input);
      break;
    case -1:
      /* Indicates end of reading */
      end_reading = true;
      break;
    case -2:
      /* Number of non integer values read from file or terminal
       * are counted.
       */
      invalid++;
      break;
    }
    /* Breaks out of loop if CTRL + D is read from terminal or
     * there are no more datas to read from file
     */
    if (end_reading) {
      break;
    }
  }
  /*After all data points are read they will be sorted in
   * accending order
   */
  vec_sort(xs);
  int sum = 0;
  /* All summed up so that to calculate an Average */
  for (int i = 0; i < (int)vec_length(xs); i++) {
    sum += *vec_at(xs, i);
  }
  /* Information can be given if there exist data points to read */
  if (vec_length(xs) > 0) {
    printf("Number of data points: %ld\n", vec_length(xs));
    printf("Minimum:               %d\n", *vec_at(xs, 0));
    printf("Lower Quartile:        %d\n", *vec_at(xs, vec_length(xs) / 4));
    printf("Median:                %d\n", *vec_at(xs, vec_length(xs) / 2));
    printf("Upper Quartile:        %d\n",
           *vec_at(xs, (3 * vec_length(xs)) / 4));
    printf("Maximum:               %d\n", *vec_at(xs, vec_length(xs) - 1));
    printf("Average:               %f\n", (float)sum / vec_length(xs));
  }
  /* Optional! */
  else {
    printf("No data point found!\n");
  }
  /*Dispaly total invalid data points if they exist*/
  if (invalid > 0) {
    printf("\n WARNING: Found %d invalid data points.\n", invalid);
  }
  vec_free(xs);
}

int main(void) { statistics(); }
