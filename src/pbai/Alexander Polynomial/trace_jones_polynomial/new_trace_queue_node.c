#include "trace_jones_polynomial.h"

/* Creates a new word_queue_node. Initializes the polynomial multiplier to 1. */
struct trace_queue_node* new_trace_queue_node(struct braid_word* word)
{
	struct trace_queue_node* result = malloc(sizeof(struct trace_queue_node));
	if (!result) {
		return (void*)0;
	}

	result->word = word;

	struct int_polynomial one = new_int_polynomial(0);
	one.coeffs[0] = 1;
	result->multiplier = &one;

	result->prev = (void*)0;
	result->next = (void*)0;

	return result;
}
