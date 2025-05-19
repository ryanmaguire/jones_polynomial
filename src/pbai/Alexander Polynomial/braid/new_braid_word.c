#include <stdlib.h>
#include "braid_knot.h"

/* Allocates memory for and returns a braid word struct given the number of strands and the length of the word */
struct braid_word* new_braid_word(size_t strands, size_t elements) 
{
	struct braid_word* result = malloc(sizeof(struct braid_word));
	if (!result) {
		return (void*)0;
	}

	result->strands = strands;
	result->elements = elements;

	result->element_array = malloc(elements * sizeof(int));
	result->exponent_array = malloc(elements * sizeof(int));

	return result;
}
