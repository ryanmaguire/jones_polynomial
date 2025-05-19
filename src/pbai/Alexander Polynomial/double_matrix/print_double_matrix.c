#include "double_matrix.h"

/* Prints the double matrix A with the given field width per element */
extern void print_double_matrix(const struct double_matrix A, const int field_width)
{
	for (unsigned int row = 0; row < A.rows; row++) {
		for (unsigned int col = 0; col < A.cols; col++) {
			printf("%*f ", field_width, A.entries[row][col]);
		}
		print("\n");
	}
}