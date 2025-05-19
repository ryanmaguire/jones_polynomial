#ifndef BRAID_KNOT_H
#define BRAID_KNOT_H

#include <stddef.h>

struct braid_word {
	size_t strands;
	size_t elements;

	int* element_array;
	int* exponent_array;
};

/* Allocates memory for and returns a braid word struct given the number of strands and the length of the word */
extern struct braid_word* new_braid_word(size_t strands, size_t elements);

/* Deallocates memory for the braid word B */
extern void destruct_braid_word(struct braid_word* B);

/* Scans the braid word B for consecutive, identical elements and simplifies them by multiplying them together */
extern struct braid_word* compress_braid_word(struct braid_word* B);

#endif