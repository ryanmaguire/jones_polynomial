#include <stdlib.h>
#include "double_matrix.h"

/* Frees memory for a double matrix */
void destruct_double_matrix(struct double_matrix A) 
{
	for (unsigned int i = 0; i < A.rows; i++) {
		free(A.entries[i]);
	}
	free(A.entries);
}