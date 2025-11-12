#include "int_polynomial_matrix.h"

/* Frees memory for a int polynomial matrix */
extern void destruct_int_polynomial_matrix(struct int_polynomial_matrix A)
{
	for (unsigned int i = 0; i < A.rows; i++) {
		free(A.entries[i]);
	}
	free(A.entries);
}