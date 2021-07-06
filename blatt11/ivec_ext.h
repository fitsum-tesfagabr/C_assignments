#ifndef IVEC_FILTER_H
#define IVEC_FILTER_H

#include "./ivec.h"

#include <stdbool.h>

void ivec_filter(IntVec* xs, bool (*f)(int));

int ivec_fold(IntVec* xs, int y, int (*f)(int, int));

int ivec_sum(IntVec* xs);

int ivec_product(IntVec* xs);

#endif /* IVEC_FILTER_H */
