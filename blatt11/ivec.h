#ifndef INT_IVEC_H
#define INT_IVEC_H

#include <stdbool.h>
#include <stddef.h>

/* Struct Declaration. The actual struct definition is hidden in `vec.c`.
 *
 * This prevents people, who are using our vector library, to directly access
 * the fields of this struct, like `capacity`. The only way to interact with the
 * vector is via the functions declared in this header.
 *
 * In other words: people using this library are not able to do stupid stuff
 * like changing the vector's capacity without also reallocating the memory area
 * of the vector.
 */
struct IntVec;

/* Allows us to write `IntVec` instead of `struct IntVec`. */
typedef struct IntVec IntVec;

/* Returns a pointer to a freshly allocated vector of length 0 and capacity 1.
 * Returns NULL if we run out of memory.
 */
IntVec* ivec_new();

/* Free the dynamically allocated memory areas of `xs`. */
void ivec_free(IntVec* xs);

/* Returns a pointer to the element at index `i` of vector `xs`. */
int* ivec_at(IntVec* xs, size_t i);

/* Returns the number of elements currently stored in `xs`. */
size_t ivec_length(IntVec* xs);

/* Returns the vector's current capacity. */
size_t ivec_capacity(IntVec* xs);

/* Append a single element `x` at the end of the vector `xs`.
 *
 * If the vector's length is equal to its capacity, the vector's data is
 * reallocated at the double of its capacity to allow for amortized constant
 * runtime.
 *
 * Returns `false` if we run out memory, otherwise `true`.
 */
bool ivec_push(IntVec* xs, int x);

/* Remove the last element of vector `xs` and return it.
 *
 * If the resulting vector's length is half of its capacity, the vector's
 * capacity is shrunk to its new length to save memory.
 */
int ivec_pop(IntVec* xs);

/* Like ivec_pop, but removes the element at a specific index. */
int ivec_remove(IntVec* xs, size_t i);

/* Print the address, length, capacity, and elements of `xs`. */
void ivec_print(IntVec* xs);

#endif /* INT_IVEC_H */
