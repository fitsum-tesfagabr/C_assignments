#ifndef BOOL_MATRIX_H
#define BOOL_MATRIX_H

#include <stdbool.h>
#include <stddef.h>
/* Representation of the terminal content as a matrix of `cells`. */
typedef struct BoolMatrix BoolMatrix;

/* Allocate a new matrix of size `width` x `height` where each cell is
 * initialized to be `def`.
 */
BoolMatrix* bool_matrix_new(size_t width, size_t height, bool def);

/* Deallocate a matrix. */
void bool_matrix_free(BoolMatrix* m);

/* Returns the width of the matrix. */
size_t bool_matrix_width(BoolMatrix* m);

/* Returns the height of the matrix. */
size_t bool_matrix_height(BoolMatrix* m);

/* Retrieve the `bool` at column `x` and row `y`. */
bool* bool_matrix_at(BoolMatrix* m, size_t x, size_t y);

#endif /* BOOL_MATRIX_H */
