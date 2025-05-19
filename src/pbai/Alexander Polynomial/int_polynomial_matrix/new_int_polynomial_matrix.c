#include <stdlib.h>
#include "int_polynomial_matrix.h"
#include "../int_polynomial/int_polynomial.h"

/* Allocates memory for and returns a int polynomial matrix struct given the rows and cols */
extern struct int_polynomial_matrix new_int_polynomial_matrix(const int new_rows, const int new_cols)
{
	struct int_polynomial_matrix result;

	result.rows = new_rows;
	result.cols = new_cols;
	result.entries = malloc(new_rows * sizeof(struct int_polynomial*));
	for (int i = 0; i < new_rows; i++) {
		result.entries[i] = malloc(new_cols * sizeof(struct int_polynomial));
	}

	return result;
}