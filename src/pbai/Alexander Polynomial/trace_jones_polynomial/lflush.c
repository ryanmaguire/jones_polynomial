#include "trace_jones_polynomial.h"
#include "../misc/misc.h"

/* Finds first and second occurences of the max element, moves them as close as possible, and updates start and end. */
void lflush(struct braid_word* word, const int max, int* const start, int* const end)
{
	/* Elements need to be at least 2 less than theis to move past start or end */
	int passthrough_wall = max;

	int passthrough_elements_count = 0;
	int stuck_elements_count = 0;

	/* Work from start forwards */
	/* Find all elements that can be flushed out the front immediately */
	for (int i = *start; i < *end; i++) {
		if (passthrough_wall - word->element_array[i] >= 2) {
			passthrough_elements_count++;
		}
		else {
			stuck_elements_count++;
			if (passthrough_wall - word->element_array[i] == 1) {
				passthrough_wall--;
			}
		}
	}

	int* passthrough_elements = malloc(passthrough_elements_count * sizeof(int));
	int* passthrough_exponents = malloc(passthrough_elements_count * sizeof(int));
	int* stuck_elements = malloc(stuck_elements_count * sizeof(int));
	int* stuck_exponents = malloc(stuck_elements_count * sizeof(int));
	if (!passthrough_elements || !stuck_elements || !passthrough_exponents || !stuck_exponents) {
		return;
	}

	int passthrough_elements_index = 0;
	int stuck_elements_index = 0;

	/* Populate arrays */
	passthrough_wall = max;
	for (int i = *start; i < *end; i++) {
		if (passthrough_wall - word->element_array[i] >= 2) {
			passthrough_elements[passthrough_elements_index++] = word->element_array[i];
			passthrough_exponents[passthrough_elements_index++] = word->exponent_array[i];
		}
		else {
			stuck_elements[stuck_elements_index++] = word->element_array[i];
			stuck_exponents[stuck_elements_index++] = word->exponent_array[i];
			if (passthrough_wall - word->element_array[i] == 1) {
				passthrough_wall--;
			}
		}
	}

	/* Update array */
	for (int i = *start; i < *start + passthrough_elements_count; i++) {
		word->element_array[i] = passthrough_elements[i - *start];
		word->exponent_array[i] = passthrough_exponents[i - *start];
	}
	for (int i = *start + passthrough_elements_count; i < *end; i++) {
		word->element_array[i] = stuck_elements[i - *start - passthrough_elements_count];
		word->exponent_array[i] = stuck_exponents[i - *start - passthrough_elements_count];
	}

	*start = *start + passthrough_elements_count;
	free(passthrough_elements);
	free(passthrough_exponents);
	free(stuck_elements);
	free(stuck_exponents);

	/* Check if we were able to squeeze all the way */
	if (*start + 1 == *end) {
		return;
	}

	/* Do the same thing except from the end */
	passthrough_wall = max;

	passthrough_elements_count = 0;
	stuck_elements_count = 0;

	/* Work from end backwards */
	/* Find all elements that can be flushed out the front immediately */
	for (int i = *end; i > *start; i--) {
		if (passthrough_wall - word->element_array[i] >= 2) {
			passthrough_elements_count++;
		}
		else {
			stuck_elements_count++;
			if (passthrough_wall - word->element_array[i] == 1) {
				passthrough_wall--;
			}
		}
	}

	passthrough_elements = malloc(passthrough_elements_count * sizeof(int));
	passthrough_exponents = malloc(passthrough_elements_count * sizeof(int));
	stuck_elements = malloc(stuck_elements_count * sizeof(int));
	stuck_exponents = malloc(stuck_elements_count * sizeof(int));
	if (!passthrough_elements || !stuck_elements || !passthrough_exponents || !stuck_exponents) {
		return;
	}

	passthrough_elements_index = 0;
	stuck_elements_index = 0;

	/* Populate arrays */
	passthrough_wall = max;
	for (int i = *end; i > *start; i--) {
		if (passthrough_wall - word->element_array[i] >= 2) {
			passthrough_elements[passthrough_elements_index++] = word->element_array[i];
			passthrough_exponents[passthrough_elements_index++] = word->exponent_array[i];
		}
		else {
			stuck_elements[stuck_elements_index++] = word->element_array[i];
			stuck_exponents[stuck_elements_index++] = word->exponent_array[i];
			if (passthrough_wall - word->element_array[i] == 1) {
				passthrough_wall--;
			}
		}
	}

	/* Update array */
	for (int i = *end; i > *end - passthrough_elements_count; i--) {
		word->element_array[i] = passthrough_elements[*end - i];
		word->exponent_array[i] = passthrough_exponents[*end - i];
	}
	for (int i = *end - passthrough_elements_count; i > *start; i--) {
		word->element_array[i] = stuck_elements[*end - passthrough_elements_count - i];
		word->exponent_array[i] = stuck_exponents[*end - passthrough_elements_count - i];
	}

	*end = *end - passthrough_elements_count;
	free(passthrough_elements);
	free(passthrough_exponents);
	free(stuck_elements);
	free(stuck_exponents);

}
