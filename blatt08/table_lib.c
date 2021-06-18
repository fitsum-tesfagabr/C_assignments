#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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
    line[success - 1] = '\0';
    return line;
  }
}

FILE** open_files(char** file_paths, size_t num_file_paths, FILE* error_file) {

  FILE** files = malloc(num_file_paths * sizeof(FILE));
  bool err_found = false; /* Check if there are errors */

  for (int i = 0; i < num_file_paths; i++) {
    /* Open File */

    if ((files[i] = fopen(file_paths[i], "r")) == NULL) {
      err_found = true;
      fprintf(error_file, "ERROR: Failed to open file \'%s\'\n", file_paths[i]);
    }
  } // end of for

  if (err_found) {
    close_files(files, num_file_paths);
    return NULL;
  }
  return files;
}

void close_files(FILE** files, size_t num_files) {
  if (files != NULL) {
    for (int i = 0; i < num_files; i++) {
      /* Only non-NULL need to be closed */
      if (files[i] != NULL) {
        fclose(files[i]);
      }
    }
    free(files);
  }
}

void merge_columns(FILE** input_files, size_t num_input_files,
                   FILE* output_file) {

  if (input_files != NULL) {
    char* tmp = NULL;
    size_t active = 1;
    while (active != 0) {
      active = 0;
      for (int j = 0; j < num_input_files; j++) {
        /* Get line by line */
        tmp = fgetline(input_files[j]);
        /* End of line not reached */
        if (tmp != NULL) {
          active++;

          if (j + 1 >= num_input_files) {
            fprintf(output_file, "%s", tmp);
          } else {
            fprintf(output_file, "%s,", tmp);
          }
          /* No need to add comma to the end*/
          free(tmp);
        } else {
          if (j + 1 != num_input_files) {
            fprintf(output_file, "%c", ',');
          }
        }
      } // end of for
      fprintf(output_file, "\n");
    } // end of while
    free(tmp);
  }
}
