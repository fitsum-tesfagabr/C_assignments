#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "./table_lib.h"

char* fgetline(FILE* file) {
  char* line = NULL;
  size_t len = 0;
  ssize_t success = getline(&line, &len, file);
  if (success <= 0) {
    free(line);
    return NULL;
  } else {
    return line;
  }
}

FILE** open_files(char** file_paths, size_t num_file_paths, FILE* error_file) {
}

void close_files(FILE** files, size_t num_files) {
}

void merge_columns(FILE** input_files, size_t num_input_files, FILE* output_file) {
}
