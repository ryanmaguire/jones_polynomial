#ifndef TRACE_JONES_H
#define TRACE_JONES_H

#include "../braid/braid_knot.h"
#include "../int_polynomial/int_polynomial.h"

struct trace_queue_node {
	struct braid_word* word;
	struct int_polynomial* multiplier;

	struct trace_queue_node* next;
	struct trace_queue_node* prev;
};

/* We will use the notation presented in An Algorithm for Calculating Jones Polynomials (1996) */

/* Creates a new trace_queue_node. Initializes the polynomial multiplier to 1. */
extern struct trace_queue_node* new_trace_queue_node(struct braid_word* word);

/* Frees the memory to a trace_queue_node */
extern void destruct_trace_queue_node(struct trace_queue_node*);

/* Calculates the sum z*Omega_1(t,k) + Omega_2(t,k) for an integer k not equal to 0 */
extern struct int_polynomial* big_omega(const int k);

/* Finds first and second occurences of the max element, moves them as close as possible, and updates start and end. */
extern void lflush(struct braid_word* word, const int max, int* const start, int* const end);

/* Takes output from lflush after compressing. Returns the index of the first 3 element sublist that can be inverted after modifying word to be in that form. */
/* Returns -1 if start and end could be merged and no such 3 element sublist exists (due to there not being 3 elements anymore */
extern int squeeze(struct braid_word* word, const int* const start, const int* const end);

/* Takes the first index of a 3 element sublist and inverts it. Returns the number of resulting branches, which are stored in results 1 through 3 */
extern int invert(struct braid_word* word, int index, struct braid_word* result1, struct braid_word* result2, struct braid_word* result3);

/* Computes the trace of the given braid word, treating the elements as members of a Iwahori-Hecke Algebra */
extern struct int_polynomial* trace(struct braid_word* word);

/* Computes the Jones Polynomial */
extern struct int_polynomial* trace_jones_polynomial(struct braid_word* word);

#endif
