#ifndef DOUBLE_MATRIX_H
#define DOUBLE_MATRIX_H

#include <stdio.h>   
#include <stdlib.h> 

/* These will be indexed by rows first and then by column */
struct double_matrix {
	unsigned int rows;
	unsigned int cols;
	
	double **entries;
};

/* Find the determinant of the given matrix A. THIS WILL MODIFY THE GIVEN STRUCT */
extern double determinant_double_matrix(struct double_matrix A);

/* Allocates memory for and returns a double matrix struct given the rows and cols */
extern struct double_matrix new_double_matrix(const int new_rows, const int new_cols);

/* Prints the double matrix A with the given field width per element */
extern void print_double_matrix(const struct double_matrix A, const int field_width);

/* Frees memory for a double matrix */
extern void destruct_double_matrix(struct double_matrix A);

#endif