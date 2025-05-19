#ifndef INT_POLY_MATRIX_H
#define INT_POLY_MATRIX_H

#include <stdio.h>   
#include <stdlib.h> 

#include "../int_polynomial/int_polynomial.h"

/* These will be indexed by rows first and then by column */
struct int_polynomial_matrix {
	unsigned int rows;
	unsigned int cols;
	
	struct int_polynomial **entries;
};

/* Returns the determinant of the given matrix A using Lagrange interpolation of a range of dim+1 integers starting from a specified lower bound */
extern struct int_polynomial determinant_int_polynomial_matrix(const struct int_polynomial_matrix A, const int lagrange_start);

/* Allocates memory for and returns a int polynomial matrix struct given the rows and cols */
extern struct int_polynomial_matrix new_int_polynomial_matrix(const int new_rows, const int new_cols);

/* Prints the int polynomial matrix A using the given char as its variable with the given field width */
extern void print_int_polynomial_matrix(const struct int_polynomial_matrix A, const char var, const int field_width);

/* Frees memory for a int polynomial matrix */
extern void destruct_int_polynomial_matrix(struct int_polynomial_matrix A);

#endif