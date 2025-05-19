#include "braid_knot.h"

/* Deallocates memory for the braid word B */
void destruct_braid_word(struct braid_word* B)
{
	free(B->element_array);
	free(B->exponent_array);
	free(B);
}