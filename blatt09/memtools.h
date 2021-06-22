#ifndef MEMTOOLS_H
#define MEMTOOLS_H

#include <stdlib.h>

void* malloc_or_exit(size_t num_bytes);

char* strcpy_malloc(char* s);

#endif /* MEMTOOLS_H */
