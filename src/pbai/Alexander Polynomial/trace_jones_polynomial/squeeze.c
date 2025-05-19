#include "trace_jones_polynomial.h"
#include "../misc/misc.h"

/* Takes output from lflush after compressing. Returns the index of the first 3 element sublist that can be inverted after modifying word to be in that form. */
/* Returns -1 if start and end could be merged and no such 3 element sublist exists (due to there not being 3 elements anymore */
int squeeze(struct braid_word* word, const int* const start, const int* const end)
{
	if (*start == *end) {
		return -1
	}

	/* The current subinterval enclosed by *start and *end is guaranteed to contain a beginning descending sequence from the first max element */
	/* We will go through until we find the first point at which this sequence ends, at which point we will set shift_index to this element */
	/* By moving this element as far left as it can go, we are guaranteed to create an invertible 3 element sublist */
	int shift_index = *start + 1;
	for (; shift_index <= *end; shift_index++) {
		if (word->element_array[shift_index - 1] - word->element_array[shift_index] != 1) {
			break;
		}
	}

	while (word->element_array[shift_index - 1] - word->element_array[shift_index] != -1) {
		swap_int(&word->element_array[shift_index - 1], &word->element_array[shift_index]);
		shift_index--;
	}

	return shift_index - 2;
}
