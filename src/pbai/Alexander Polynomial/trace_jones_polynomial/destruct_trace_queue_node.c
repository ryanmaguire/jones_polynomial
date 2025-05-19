#include "trace_jones_polynomial.h"

/* Frees the memory to a word_queue_node */
void destruct_trace_queue_node(struct trace_queue_node* node)
{
	destruct_braid_word(node->word);
	free(node->multiplier->coeffs);
	free(node);
}
