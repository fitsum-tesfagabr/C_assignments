#ifndef CSV_FROM_FILES_LIB_H
#define CSV_FROM_FILES_LIB_H

#include <stddef.h>
#include <stdio.h>

/* Read a line from a file. Returns `NULL` if an error occurs or the end of the
 * file is reached.
 */
char* fgetline(FILE* file);

FILE** open_files(char** file_paths, size_t num_file_paths, FILE* error_file);

void close_files(FILE** files, size_t num_files);

void merge_columns(FILE** input_files, size_t num_input_files,
                   FILE* output_file);

#endif /* CSV_FROM_FILES_LIB_H */
