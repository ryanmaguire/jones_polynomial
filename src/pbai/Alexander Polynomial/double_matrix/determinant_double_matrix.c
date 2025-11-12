#include "double_matrix.h"

/* This function will return the integer determinant of the given matrix A. THIS WILL MODIFY THE GIVEN STRUCT */

/* We will proceed by finding an LU factorization while keeping track of how many row swaps we have done to get the determinant sign */
/* We will slowly do operations on A to make it into an upper triangular matrix U */
/* Notice that we don't even need to keep track of L because we can ensure that the elements on the main diagonal of L will all be 1 */
double determinant_double_matrix(struct double_matrix A)
{
	int dimension = A.rows;

	/* Not needed due to reasons explained above */
	// struct double_matrix L = new_double_matrix(A.rows, A.cols);

	/* This will flip between 1 and -1 to keep track of row operations */
	/* We will use this instead of keeping track of an entire permutation matrix */
	int sign = 1;

	/* Other variables that we will use later */
	int max_index;
	double max, temp_double, multiplier;
	double *temp_double_ptr;

	/* Main loop through each column 0 - this corresponds to looking at the element at (k,k) and all the rows below it */
	for (int k = 0; k < dimension; k++) {
		/* We will begin each loop by first looking for the element in the column with the largest absolute value */
		max = 0;
		max_index = -1;
		for (int row = k; row < dimension; row++) {
			temp_double = (A.entries[row][k] < 0) ? (-1 * A.entries[row][k]) : A.entries[row][k]; // temp_double is the abs of the entry
			if (temp_double > max) {
				max = temp_double;
				max_index = row;
			}
		}

		/* If max is never updated, then the entire column is zero, so the matrix is not of full rank and the determinant is 0 */
		if (max_index == -1) {
			return 0;
		}

		/* Otherwise, we have the index of the largest element. We will swap rows k and max_index - this is for numerical stability purposes */
		if (max_index != k) {
			temp_double_ptr = A.entries[k];
			A.entries[k] = A.entries[max_index];
			A.entries[max_index] = temp_double_ptr;
			sign *= -1;
		}

		/* Now, we can subtract an appropriate multiple of row k from each of the rows below it */
		for (int row = k+1; row < dimension; row++) {
			multiplier = A.entries[row][k] / A.entries[k][k]; // Scalar to multiply row k by
			
			A.entries[row][k] = 0; // Make sure this is zero - avoids precision issues
			for (int col = k + 1; col < dimension; col++) {
				A.entries[row][col] -= multiplier * A.entries[k][col];
			}
		}
	}

	/* We have now turned A into an upper triangular matrix! The determinant is the product of the diagonal entries and the sign */
	double result = sign;
	for (int i = 0; i < dimension; i++) {
		result *= A.entries[i][i];
	}

	return result;
}