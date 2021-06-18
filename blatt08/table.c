#include <stdio.h>
#include <stdlib.h>

#include "./table_lib.h"

int main(int argc, char** argv) {
  if (argc < 2) {
    printf("USAGE: ./table <filename1> <filename2> ...\n");
    exit(1);
  }
  char* file_paths[argc - 1];
  for (int i = 1; i < argc; i++) {
    file_paths[i - 1] = argv[i];
  }
  FILE** files = open_files(file_paths, argc - 1, stderr);
  merge_columns(files, argc - 1, stdout);

  close_files(files, argc - 1);
  return 0;
}
