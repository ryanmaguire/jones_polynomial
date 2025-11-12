#include <stdlib.h>
#include <math.h>
#include "int_polynomial_matrix.h"
#include "../double_polynomial/double_polynomial.h"
#include "../double_matrix/double_matrix.h"

struct int_polynomial determinant_int_polynomial_matrix(const struct int_polynomial_matrix A, const int lagrange_start) 
{
	int dimension = A.rows;

	/* The values array will hold all of the values obtained by evaluating the determinants at integers in the range */
	/* Index i in the values array will correspond to n = i + lagrange_start */
	int *values = (int*) malloc((dimension + 1) * sizeof(int));
	if (!values) { // cooked
		free(values);
		return new_int_polynomial(0);
	}

	/* Fill up the values array by calculating determinants */
	/* This is the O(n^4) step, I should figure out how to get it to O(n^3) later */
	for (int n = lagrange_start; n <= lagrange_start + dimension; n++) {
		struct double_matrix eval_matrix = new_double_matrix(dimension, dimension);

		for (int row = 0; row < dimension; row++) {
			for (int col = 0; col < dimension; col++) {
				eval_matrix.entries[row][col] = evaluate_int_polynomial_int(A.entries[row][col], n);
			}
		}

		values[n - lagrange_start] = (int) round(determinant_double_matrix(eval_matrix));

		destruct_double_matrix(eval_matrix); // Free up memory since we won't use this again
	}

	/* This will store the polynomials in the Lagrange Basis */
	/* We will add scalar multiples of everything in here as our last step in Lagrange Interpolation */
	struct double_polynomial *lagrange_basis = (struct double_polynomial*) malloc((dimension + 1) * sizeof(struct double_polynomial));
	if (!lagrange_basis) { // cooked
		free(lagrange_basis);
		return new_int_polynomial(0);
	}

	/* We will use this later to avoid memory leak */
	struct double_polynomial temp_double_polynomial;

	/* Fill up the Lagrange Basis array */
	/* n is which integer in the range we are building an element of the Lagrange Basis around (multiply everything except the terms with this integer) */
	for (int n = lagrange_start; n <= lagrange_start + dimension; n++) {
		/* Initialize the current basis element to the constant polynomial equal to 1. We will multiply this by stuff as we go */
		struct double_polynomial current_basis_element = new_double_polynomial(0);
		current_basis_element.coeffs[0] = 1;

		/* k is the current term that we are multiplying */
		for (int k = lagrange_start; k <= lagrange_start + dimension; k++) {
			/* We don't want k=n */
			if (k == n) {
				continue;
			}

			struct double_polynomial next_term = new_double_polynomial(1);

			/* next_term should equal (x-k)/(n-k) where x is the variable in the polynomial */
			double denominator = n - k;
			next_term.coeffs[1] = 1 / denominator;
			next_term.coeffs[0] = -k / denominator;

			temp_double_polynomial = multiply_double_polynomial(next_term, current_basis_element);
			/* We don't need these two any more after we obtain their product, so we shall free them */
			free(current_basis_element.coeffs);
			free(next_term.coeffs);
			/* Assign temp_double_polynomial back to current_basis_element */
			current_basis_element = temp_double_polynomial;
		}

		lagrange_basis[n - lagrange_start] = scale_double_polynomial(current_basis_element, values[n - lagrange_start]);
		free(current_basis_element.coeffs);
	}

	/* We are done with the values */
	free(values);

	/* Add everything together to get the final polynomial */

	/* Set up final double polynomial */
	struct double_polynomial double_result = new_double_polynomial(dimension);
	/* Initialize double_result to all 0's */
	for (unsigned int i = 0; i <= double_result.degree; i++) {
		double_result.coeffs[i] = 0;
	}

	/* Addition time */
	for (int i = 0; i <= dimension; i++) {
		temp_double_polynomial = add_double_polynomial(double_result, lagrange_basis[i]);
		/* We don't need these two any more after we obtain their product, so we shall free them */
		free(lagrange_basis[i].coeffs);
		/* Assign temp_double_polynomial back to current_basis_element */
		double_result = temp_double_polynomial;
	}

	free(lagrange_basis);

	/* Find real degree of polynomial (check for leading zeroes in coeffs) */
	int real_degree = double_result.degree;
	while (0 == (int) round(double_result.coeffs[real_degree])) {
		real_degree--;
	}

	struct int_polynomial int_result = new_int_polynomial(real_degree);

	/* Round all coefficients of int_result */
	for (unsigned int i = 0; i <= int_result.degree; i++) {
		int_result.coeffs[i] = (int) round(double_result.coeffs[i]);
	}

	free(double_result.coeffs);

	return int_result;
}