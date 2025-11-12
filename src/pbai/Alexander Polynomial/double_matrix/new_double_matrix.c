#include <stdlib.h>
#include "double_matrix.h"

/* Allocates memory for and returns a double matrix struct given the rows and cols */
struct double_matrix new_double_matrix(const int new_rows, const int new_cols)
{
	struct double_matrix result;

	result.rows = new_rows;
	result.cols = new_cols;
	result.entries = malloc(new_rows * sizeof(double*));
	for (int i = 0; i < new_rows; i++) {
		result.entries[i] = malloc(new_cols * sizeof(double));
	}

	return result;
}