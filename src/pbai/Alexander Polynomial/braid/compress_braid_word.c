#include "braid_knot.h"

/* Scans the braid word B for consecutive, identical elements and simplifies them by multiplying them together */
struct braid_word* compress_braid_word(struct braid_word* B)
{
	if (B->elements == 0) {
		return new_braid_word(B->strands, 0);
	}

	/* Find the length of the compressed braid word */
	int previous_element = B->element_array[0];
	int new_length = 1;
	for (int i = 1; i < B->elements; i++) {
		if (B->element_array[i] != previous_element) {
			new_length++;
		}
		previous_element = B->element_array[i];
	}

	/* Create the compressed braid word with the found length */
	struct braid_word* result = new_braid_word(B->strands, new_length);

	previous_element = B->element_array[0];
	int current_exponent = B->exponent_array[0];
	int result_index = 0;

	for (int i = 1; i < B->elements; i++) {
		if (B->element_array[i] != previous_element) {
			result->element_array[result_index] = previous_element;
			result->exponent_array[result_index] = current_exponent;
			result_index++;

			current_exponent = B->exponent_array[i];
		}
		else {
			current_exponent += B->exponent_array[i];
		}

		previous_element = B->element_array[i];
	}

	/* Finish up last element of result */
	result->element_array[result_index] = previous_element;
	result->exponent_array[result_index] = current_exponent;

	return result;
	
}