#ifndef PD_CODE_KNOT_H
#define PD_CODE_KNOT_H

#include "../int_polynomial/int_polynomial.h"
#include "../int_polynomial_matrix/int_polynomial_matrix.h"

/* Arcs are numbered starting from the under arc going into the crossing and proceeding clockwise */
/* NUMBERING SHOULD START FROM ZERO */
struct crossing {
	unsigned int arcs[4];
};

struct pd_code_node {
	struct crossing* tuple;
	
	struct pd_code_node* next;
	struct pd_code_node* prev;
};

/* Returns a pointer to a new pd_code_node struct */
extern struct pd_code_node* new_pd_code_node(struct crossing* C);

/* Compute the Alexander Polynomial of a knot given an arbitrary node of its PD code representation */
extern struct int_polynomial pd_code_alexander_polynomial(struct pd_code_node* K);

#endif