#ifndef GAME_MATRIX_H
#define GAME_MATRIX_H

#include "../tui/tui.h"
#include <stddef.h>
/* Representation of the terminal content as a matrix of `cells`. */
typedef struct GameMatrix GameMatrix;

/* Allocate a new matrix of size `width` x `height` where each cell is
 * initialized to be `def`.
 */
GameMatrix* game_matrix_new(size_t width, size_t height, Cell* def);

/* Deallocate a matrix. */
void game_matrix_free(GameMatrix* m);

/* Returns the width of the matrix. */
size_t game_matrix_width(GameMatrix* m);

/* Returns the height of the matrix. */
size_t game_matrix_height(GameMatrix* m);

/* Retrieve the `bool` at column `x` and row `y`. */
Cell* game_matrix_at(GameMatrix* m, size_t x, size_t y);

#endif /* BOOL_MATRIX_H */
