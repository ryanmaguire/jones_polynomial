#include "int_polynomial_matrix.h"
#include "../int_polynomial/int_polynomial.h"

/* Prints the int polynomial matrix A using the given char as its variable with the given field width */
extern void print_int_polynomial_matrix(const struct int_polynomial_matrix A, const char var, const int field_width)
{
	/* We will use this for keeping track of field widths */
	int current_width;

	for (unsigned int row = 0; row < A.rows; row++) {
		for (unsigned int col = 0; col < A.cols; col++) {
			current_width = print_int_polynomial(A.entries[row][col], var);
			// Add one space for spacing between polynomials
			printf("%*s", 1 + field_width - current_width, "");
		}
		printf("\n");
	}
}