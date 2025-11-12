#include "double_polynomial.h"

/* Multiplies double polynomials a and b using naive O(nm) multiplication, returns the result */
struct double_polynomial multiply_double_polynomial(const struct double_polynomial P, const struct double_polynomial Q)
{
	struct double_polynomial result = new_double_polynomial(P.degree + Q.degree);

	// Initialize everything in result to 0
	for (unsigned int i = 0; i <= result.degree; i++) {
		result.coeffs[i] = 0;
	}

	for (unsigned int p_index = 0; p_index <= P.degree; p_index++) {
		for (unsigned int q_index = 0; q_index <= Q.degree; q_index++) {
			result.coeffs[p_index + q_index] += P.coeffs[p_index] * Q.coeffs[q_index];
		}
	}

	return result;
}
